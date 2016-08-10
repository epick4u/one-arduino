package com.onelab.arduino.breakfast.controller;

import java.util.Calendar;
import java.util.Date;
import java.util.List;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import com.onelab.arduino.breakfast.repository.RecipientRepository;
import com.onelab.arduino.breakfast.repository.entity.RecipientVO;
import com.onelab.arduino.common.repository.entity.EmployeeVO;

@CrossOrigin(origins = "*")
@RestController(value="/breakfast")
public class BreakfastController implements InitializingBean {

	private static final int TotalCount = 40;
	
	private Date startDate;
	private Date endDate;
	
	@Autowired
	RecipientRepository recipientRepository;
	
	/**
	 * 조식 현황 (남은 수량)
	 * TODO 사용자가 menu 입력시 해당 정보도 반영
	 * @return
	 */
	@RequestMapping(value="/status", method=RequestMethod.GET)
    public @ResponseBody BreakfastStatusVO getStatus() {
		
		int receiptCount = recipientRepository.countByReceiptDateBetween(startDate, endDate);
		
		BreakfastStatusVO statusVO = new BreakfastStatusVO(); 
		statusVO.setDate(new Date());
		statusVO.setTotalCount(TotalCount);
		statusVO.setLeftCount(TotalCount - receiptCount);
		
        return statusVO;
    }
	
	@RequestMapping(value="/photo", method=RequestMethod.GET)
    public @ResponseBody void getPhoto() {
		
        return;
    }
	
	@RequestMapping(value="/photo", method=RequestMethod.POST)
    public @ResponseBody void updatePhoto() {
		
        return;
    }
	
	/**
	 * 금일 기준 수령 현황 반환
	 */
	@RequestMapping(value="/recipient", method=RequestMethod.GET)
    public @ResponseBody List<RecipientVO> getRecipients() {		
		
        return recipientRepository.findByReceiptDateBetween(startDate, endDate);
    }
	
	/**
	 * 호출된 시간을 기준으로 수령 정보 저장
	 * @param employeeCardId
	 */
	@RequestMapping(value="/recipient/{employeeCardId}", method=RequestMethod.PUT)
    public @ResponseBody void insertRecipient(@PathVariable String employeeCardId) {
		
		EmployeeVO employeeVO = new EmployeeVO();
		employeeVO.setCardId(employeeCardId);
		
		
		RecipientVO recipientVO =  new RecipientVO();
		recipientVO.setEmployee(employeeVO);
		recipientVO.setReceiptDate(new Date());
		
        recipientRepository.save(recipientVO);
    }
	
	/**
	 * 당일 00~24 셋팅
	 * 빈 초기 로드시, 매일 자정 호출되어 리셋됨.
	 */
	@Scheduled(cron="0 0 0 * *")
	private void resetDateRange() {
		
		Calendar calendar = Calendar.getInstance();
		
		calendar.set(Calendar.HOUR_OF_DAY, 0);
		this.startDate = calendar.getTime();
		
		calendar.add(Calendar.HOUR_OF_DAY, 24);
		this.endDate = calendar.getTime();
	}
	
	@Override
	public void afterPropertiesSet() throws Exception {
		resetDateRange();
	}
}
