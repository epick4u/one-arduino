package com.onelab.arduino.common.repository;

import com.onelab.arduino.common.repository.entity.NickName;
import org.springframework.data.repository.CrudRepository;

public interface NickNameRepository extends CrudRepository<NickName, String> {

	public NickName findBySeq(Long seq);

}
