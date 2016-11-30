package com.onelab.arduino.common.repository.entity;

import javax.persistence.*;

@Entity(name="nickname")
public class NickNameVO {

	@Id
	@Column(unique = true, nullable = false)
	Long seq;

	@Column(unique = true, nullable = false)
	String nickName;

	@Column(unique = true)
	Long employeeSeq;

	@Column
	String imgUrl;

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

	public Long getEmployeeSeq() {
		return employeeSeq;
	}

	public void setEmployeeSeq(Long employeeSeq) {
		this.employeeSeq = employeeSeq;
	}

	public String getImgUrl() {
		return imgUrl;
	}

	public void setImgUrl(String imgUrl) {
		this.imgUrl = imgUrl;
	}
}
