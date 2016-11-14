package com.onelab.arduino.common.service;

import com.onelab.arduino.common.repository.NickNameRepository;
import com.onelab.arduino.common.repository.entity.NickNameVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Random;

/**
 * Created by 1001256 on 2016. 11. 7..
 */
@Service
public class NickNameService {

    @Autowired
    private NickNameRepository nickNameRepository;

    public NickNameVO createNickName(long employeeSeq){
        List<NickNameVO> nickNames = nickNameRepository.findByEmployeeSeqIsNull();

        int count = nickNames.size();
        if(count > 0){
            Random random = new Random(count);
            int randomInt = Math.abs(random.nextInt());
            int pos = randomInt%count;
            NickNameVO nickName = nickNames.get(pos);
            nickName.setEmployeeSeq(employeeSeq);
            nickNameRepository.save(nickName);
            return nickName;
        }

        return null;
    }
}
