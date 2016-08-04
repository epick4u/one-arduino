package com.onelab.arduino.breakfast.repository;

import org.springframework.data.repository.CrudRepository;

import com.onelab.arduino.breakfast.repository.entity.RecipientVO;

public interface RecipientRepository extends CrudRepository<RecipientVO, Long> {

}
