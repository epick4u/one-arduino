package com.onelab.arduino.breakfast.repository;

import java.util.Date;
import java.util.List;

import org.springframework.data.repository.CrudRepository;

import com.onelab.arduino.breakfast.repository.entity.RecipientVO;

public interface RecipientRepository extends CrudRepository<RecipientVO, Long> {

	int countByReceiptDateBetween(Date start, Date end);
	
	List<RecipientVO> findByReceiptDateBetween(Date start, Date end);
}
