package com.onelab.arduino.sample;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.web.bind.annotation.*;

import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

@RestController
public class MainController implements InitializingBean {
	
	private Map<String, RoomVO> roomMap;
 
    @RequestMapping(value="/restroom", method=RequestMethod.GET)
    public @ResponseBody Collection<RoomVO> selectList() {
        return roomMap.values();
    }
    @RequestMapping(value="/restroom/{roomId}", method=RequestMethod.GET)
    public @ResponseBody RoomVO select(@PathVariable String roomId) {
        return roomMap.get(roomId);
    }
    
    @RequestMapping(value="/restroom/{roomId}", method=RequestMethod.POST)
    @ResponseBody
    public void update(@PathVariable String roomId) {
    	if (roomId == null && roomMap.containsKey(roomId)) {
    		return;
    	}
    		
    	RoomVO room = new RoomVO();
    	room.setId(roomId);
    	room.setStartTime(new Date());
    	
    	roomMap.put(roomId, room);
    }
    
    @RequestMapping(value="/restroom/{roomId}", method = RequestMethod.DELETE)
    @ResponseBody
    public void delete(@PathVariable String roomId) {
    	if (roomId == null || !roomMap.containsKey(roomId)) {
    		return;
    	}
    	
    	roomMap.remove(roomId);
    }

	@Override
	public void afterPropertiesSet() throws Exception {
		roomMap = new HashMap<String, RoomVO>();

		// Load temporary data to the hash map until we have database set up.
		for (int i = 0; i < 12; i++) {
			int floorNo = i / 3 + 10;
			int roomNo = i % 3 + 1;
			String restroomId = floorNo + "-" + roomNo;

			RoomVO restRoom = new RoomVO();
			restRoom.setId(restroomId);
			if (i % 2 == 0) {
				restRoom.setStartTime(new Date());
			}
			roomMap.put(restroomId, restRoom);
		}
	}

}
