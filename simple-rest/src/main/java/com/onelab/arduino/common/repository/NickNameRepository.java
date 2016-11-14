package com.onelab.arduino.common.repository;

import com.onelab.arduino.common.repository.entity.NickNameVO;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface NickNameRepository extends CrudRepository<NickNameVO, String> {

    public List<NickNameVO> findByEmployeeSeqIsNull();

}
