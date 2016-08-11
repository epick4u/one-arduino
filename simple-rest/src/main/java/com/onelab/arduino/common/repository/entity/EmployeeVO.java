package com.onelab.arduino.common.repository.entity;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity(name="employee")
public class EmployeeVO {
	
	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	Long seq;
	
	@Column(unique = true, nullable = false)
	String cardId;
	
	@Column(nullable = true)
	String name;
	
	@Column(nullable = true)
	String team;

	public Long getSeq() {
		return seq;
	}

	public void setSeq(Long seq) {
		this.seq = seq;
	}

	public String getCardId() {
		return cardId;
	}

	public void setCardId(String cardId) {
		this.cardId = cardId;
	}

	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public String getTeam() {
		return team;
	}
	
	public void setTeam(String team) {
		this.team = team;
	}
}
