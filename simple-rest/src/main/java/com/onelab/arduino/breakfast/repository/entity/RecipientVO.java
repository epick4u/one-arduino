package com.onelab.arduino.breakfast.repository.entity;

import com.onelab.arduino.common.repository.entity.EmployeeVO;

import javax.persistence.*;
import java.util.Date;

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

	@Column(nullable = false)
	String menu;
	
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

	public String getMenu() {
		return menu;
	}

	public void setMenu(String menu) {
		this.menu = menu;
	}
}
