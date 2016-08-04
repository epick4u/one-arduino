package com.onelab.arduino.breakfast.controller;

import java.util.Collection;
import java.util.Map;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import com.onelab.arduino.restroom.RoomVO;

@CrossOrigin(origins = "*")
@RestController(value="/breakfast")
public class BreakfastController {

	@RequestMapping(value="/status", method=RequestMethod.GET)
    public @ResponseBody void selectStatus() {
		
        return;
    }
}
