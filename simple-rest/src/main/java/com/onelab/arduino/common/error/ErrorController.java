package com.onelab.arduino.common.error;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by 9230095 on 2017. 12. 4..
 */
@RequestMapping("/error")
@Controller
public class ErrorController {

    public Map<String, Object> defaultError() {
        HashMap<String, Object> errorInfo = new HashMap<>();

        return errorInfo;
    }
}
