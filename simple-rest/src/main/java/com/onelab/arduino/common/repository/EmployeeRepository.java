package com.onelab.arduino.common.repository;

import org.springframework.data.repository.CrudRepository;

import com.onelab.arduino.common.repository.entity.EmployeeVO;

public interface EmployeeRepository extends CrudRepository<EmployeeVO, String> {

}
