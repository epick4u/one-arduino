package com.onelab.arduino.common.repository.entity;

import javax.persistence.*;

@Entity(name="nickname")
public class NickName {

	@Id
	@Column(unique = true, nullable = false)
	String nickName;

	public String getNickName() {
		return nickName;
	}

	public void setNickName(String nickName) {
		this.nickName = nickName;
	}

}
