package com.onelab.arduino.meetingroom;

/**
 * Created by 9230095 on 2017. 6. 19..
 */
public class MeetingRoomVO {

    private String roomId;
    private String roomName;
    private int floor;
    private boolean occupied;

    public MeetingRoomVO(String roomId, String roomName, int floor) {
        this.roomId = roomId;
        this.roomName = roomName;
        this.floor = floor;
        this.occupied = false;
    }

    public String getRoomId() {
        return roomId;
    }

    public void setRoomId(String roomId) {
        this.roomId = roomId;
    }

    public String getRoomName() {
        return roomName;
    }

    public void setRoomName(String roomName) {
        this.roomName = roomName;
    }

    public int getFloor() {
        return floor;
    }

    public void setFloor(int floor) {
        this.floor = floor;
    }

    public boolean isOccupied() {
        return occupied;
    }

    public void setOccupied(boolean occupied) {
        this.occupied = occupied;
    }
}
