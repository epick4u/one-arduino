package com.onelab.arduino.breakfast.repository.entity;

import java.util.Date;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;

import com.onelab.arduino.common.repository.entity.EmployeeVO;

@Entity(name="recipient")
public class RecipientVO {
	
	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	long seq;
	
	@ManyToOne(targetEntity=EmployeeVO.class)
	@JoinColumn(name="card_id")
	EmployeeVO employee;
	
	@Column(nullable = false)
	Date receiptDate;
	
	public long getSeq() {
		return seq;
	}

	public void setSeq(long seq) {
		this.seq = seq;
	}

	public EmployeeVO getEmployee() {
		return employee;
	}

	public void setEmployee(EmployeeVO employee) {
		this.employee = employee;
	}

	public Date getReceiptDate() {
		return receiptDate;
	}

	public void setReceiptDate(Date receiptDate) {
		this.receiptDate = receiptDate;
	}
}
