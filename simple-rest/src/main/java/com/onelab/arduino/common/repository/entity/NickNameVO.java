package com.onelab.arduino.common.repository.entity;

import javax.persistence.*;

@Entity(name="nickname")
public class NickNameVO {

	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	Long seq;

	@Column(unique = true, nullable = false)
	String nickName;

	public String getNickName() {
		return nickName;
	}

	public void setNickName(String nickName) {
		this.nickName = nickName;
	}

	public Long getSeq() {
		return seq;
	}

	public void setSeq(Long seq) {
		this.seq = seq;
	}
}
