package com.onelab.arduino.breakfast.controller;

import java.util.Date;

public class BreakfastStatusVO {
	
	Date date;
	int leftCount;
	int totalCount;
	
	public Date getDate() {
		return date;
	}
	
	public void setDate(Date date) {
		this.date = date;
	}
	
	public int getLeftCount() {
		return leftCount;
	}
	
	public void setLeftCount(int leftCount) {
		this.leftCount = leftCount;
	}
	
	public int getTotalCount() {
		return totalCount;
	}
	
	public void setTotalCount(int totalCount) {
		this.totalCount = totalCount;
	}
}
