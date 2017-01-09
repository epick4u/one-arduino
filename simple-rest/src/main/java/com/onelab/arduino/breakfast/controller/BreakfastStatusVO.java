package com.onelab.arduino.breakfast.controller;

import java.util.Date;

public class BreakfastStatusVO {
	
	Date date;
	int breadLeftCount;
	int riceLeftCount;
	boolean soldout;

	public Date getDate() {
		return date;
	}
	
	public void setDate(Date date) {
		this.date = date;
	}

	public int getBreadLeftCount() {
		return breadLeftCount;
	}

	public void setBreadLeftCount(int breadLeftCount) {
		this.breadLeftCount = breadLeftCount;
	}

	public int getRiceLeftCount() {
		return riceLeftCount;
	}

	public void setRiceLeftCount(int riceLeftCount) {
		this.riceLeftCount = riceLeftCount;
	}

	public boolean isSoldout() {
		return soldout;
	}

	public void setSoldout(boolean soldout) {
		this.soldout = soldout;
	}
}
