package com.onelab.arduino.sample;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MainController implements InitializingBean {
	
	private Map<String, RoomVO> roomMap;
 
    @RequestMapping(value="/restroom", method=RequestMethod.GET)
    public @ResponseBody Set<Entry<String, RoomVO>> selectList() {
        return roomMap.entrySet();
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
	}
}
