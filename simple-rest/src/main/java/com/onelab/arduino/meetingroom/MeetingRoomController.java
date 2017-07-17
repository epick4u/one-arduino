package com.onelab.arduino.meetingroom;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by 9230095 on 2017. 6. 19..
 */
@RestController
@RequestMapping("/meetingroom")
public class MeetingRoomController implements InitializingBean {

    private Map<String, MeetingRoomVO> roomMap;

    @RequestMapping(method=RequestMethod.GET)
    @ResponseBody
    public Collection<MeetingRoomVO> selectList() {
        return roomMap.values();
    }

    @RequestMapping(value="/{roomId}/{operation}", method=RequestMethod.GET)
    @ResponseBody
    public void inOrOut(@PathVariable String roomId, @PathVariable String operation) {
        if (roomId == null && roomMap.containsKey(roomId)) {
            System.out.println(roomId + "doesn't exist.!");
            return;
        }

        MeetingRoomVO restroom = roomMap.get(roomId);
        if ("in".equals(operation)) {
            restroom.setOccupied(true);
        } else {
            restroom.setOccupied(false);
        }
    }

    @Override
    public void afterPropertiesSet() throws Exception {
        roomMap = new HashMap<String, MeetingRoomVO>();
        roomMap.put("1", new MeetingRoomVO("1","meetingroom1",13));
        roomMap.put("2", new MeetingRoomVO("2","meetingroom2",13));
        roomMap.put("3", new MeetingRoomVO("3","meetingroom3",13));

        roomMap.put("4", new MeetingRoomVO("4","books",12));
        roomMap.put("5", new MeetingRoomVO("5","music",12));
        roomMap.put("6", new MeetingRoomVO("6","shopping",12));
        roomMap.put("11", new MeetingRoomVO("11","webtoon",12));

        roomMap.put("7", new MeetingRoomVO("7","movie",11));
        roomMap.put("8", new MeetingRoomVO("8","comic",11));
        roomMap.put("9", new MeetingRoomVO("9","game",11));

        roomMap.get("2").setOccupied(true);
    }
}
