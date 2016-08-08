package com.onelab.arduino.breakfast.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import com.onelab.arduino.breakfast.repository.RecipientRepository;

@CrossOrigin(origins = "*")
@RestController(value="/breakfast")
public class BreakfastController {

	@Autowired
	RecipientRepository recipientRepository;
	
	@RequestMapping(value="/status", method=RequestMethod.GET)
    public @ResponseBody void getStatus() {
		
//		recipientRepository.
//		.count()
		
        return;
    }
	
	@RequestMapping(value="/photo", method=RequestMethod.GET)
    public @ResponseBody void getPhoto() {
		
        return;
    }
	
	@RequestMapping(value="/photo", method=RequestMethod.POST)
    public @ResponseBody void updatePhoto() {
		
        return;
    }
	
	@RequestMapping(value="/recipient", method=RequestMethod.GET)
    public @ResponseBody void getRecipients() {
		
        return;
    }
	
	@RequestMapping(value="/recipient", method=RequestMethod.PUT)
    public @ResponseBody void insertRecipient() {
		
        return;
    }
}
