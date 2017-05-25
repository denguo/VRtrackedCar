/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define n_sensors 4

/*------speed control------*/
// constants
double circumference = 7.63;      // inches/revolution
int clock_freq = 10000;           // 10 kHz = counts/sec
int n_sensors_per_rev = 5;
int inches_per_foot = 12;
int max_timer_count = 65536;

double target_speed = 4.0;        // feet/sec
int previous_capture;

double kp;                        // PID proportional term constant
double ki;                        // PID integral term constant
double err_current;               // current error value
double speed;

double delta_t;                   // time between measurements, used in integral term
double output_current;            // current PWM duty cycle output
double error_sum;
double weight;
int output_initial;

int i;
int j;

/*------infrared tracking------*/
int inf_clk = 24; //(MHz)
int inf_timer_count = 16777216;
int timing_tolerance = 5;

int inf_rise[n_sensors];
int inf_rise_prev[n_sensors];
int inf_fall[n_sensors];
int risingEdge[n_sensors];
int dx[n_sensors];
int dy[n_sensors];
int n_fallingEdges[n_sensors];

int skip;
int axis[n_sensors];

double sync_width;
int inf_dbg;
int xUpdated;
int yUpdated;
int dbg3;

int activate_0 = 1;
int activate_1 = 2;
int activate_2 = 4;
int activate_3 = 8;
int time_slice = 10;

static void zeroIntArr(int arr[], int length) {
    int i;
    for (i = 0; i < length; i++) {
        arr[i] = 0;
    }
    return;
}

static void sendWireless(int id, int dt, int axis) {
    UART_PutChar('s');
    UART_PutChar(id);
    UART_PutChar(axis);
    
    // big endian byte order
    UART_PutChar((char) dt & 0xff);
    UART_PutChar((char) (dt >> 8) & 0xff);
    UART_PutChar((char) (dt >> 16) & 0xff);
}

static void updateSensorPos(int id) {
    int n_counts;
    if (inf_fall[id] > inf_rise[id]) {
        n_counts = inf_fall[id] - inf_rise[id];
    }
    else {
        n_counts = inf_fall[id] + (inf_timer_count - inf_rise[id]);
    }
    
    int sync_width = n_counts / inf_clk;
    if (sync_width < 40) {
        int dt;
        if (inf_rise_prev[id] > inf_fall[id]) {
            dt = inf_rise_prev[id] - inf_fall[id];
        }
        else {
            dt = inf_rise_prev[id] + (inf_timer_count - inf_fall[id]);
        }
        
        if (axis[id] == 0) {
            dx[id] = dt;
        }
        else {
            dy[id] = dt;
        }
    }
    else if (abs(sync_width - 63) <= timing_tolerance) {
        axis[id] = 0;
    }
    else if (abs(sync_width - 73) <= timing_tolerance) {
        axis[id] = 1;
    }
    else if (abs(sync_width - 83) <= timing_tolerance) {
        axis[id] = 0;
    }
    else if (abs(sync_width - 94) <= timing_tolerance) {
        axis[id] = 1;
    }
    return;
}

/*
int bufferFull(int[] dx, int[] dy) {
    for (i = 0; i < n_sensors - 1; i++) {
        if (dx == 0 || dy == 0) {
            return 0;
        }
    }
    return 1;
}*/

CY_ISR(inter_HE)
{   
    //char strbuffer[15];
    int current_capture = (int) Timer_HE_ReadCapture();
    int counts = 0;
    
    if (current_capture > previous_capture) {   // rollover
        counts = max_timer_count - current_capture + previous_capture;
    }
    else {
        counts = previous_capture - current_capture;
    }
    previous_capture = current_capture;
    
    // on first loop through interrupt function, make sure error starts positive by setting speed initially to 0
    if (i == 0) {
        speed = 0;
        i = 1;
    }
    else {
        speed = (double) (circumference * clock_freq) / (counts * n_sensors_per_rev * inches_per_foot);  // feet/sec
    }
    
    err_current = target_speed - speed;
    
    error_sum = error_sum + err_current;
    output_current = (kp*err_current) + (ki*error_sum);   // PI control calculation
    
    // 0 bound guard
    if (output_current < 0) output_current = 0;
    
    // if two laps have been completed, set output to zero
    //if (HE_interrupt_count > HE_interrupts_final) output_current = 0;
    
    // set new duty cycle 
    PWM_Motor_WriteCompare(output_current); 
    /*
    sprintf(strbuffer, "%i", HE_interrupt_count);
    LCD_Position(1,0);
    LCD_PrintString(strbuffer);
    */
    
    //HE_interrupt_count += 1;
}

// 1
CY_ISR(inter_infrared_rising_0) {
    inf_rise_prev[0] = inf_rise[0];
    inf_rise[0] = (int) Timer_Infrared_0_ReadCapture();
    updateSensorPos(0);
}

CY_ISR(inter_infrared_falling_0) {
    char strbuffer[15];
    inf_fall[0] = (int) Timer_Infrared_0_ReadCapture();
    n_fallingEdges[0] += 1;
    
    sprintf(strbuffer, "%i", n_fallingEdges[0]);
    LCD_Position(0,0);
    LCD_PrintString(strbuffer);
}

// 2
CY_ISR(inter_infrared_rising_1) {
    inf_rise_prev[1] = inf_rise[1];
    inf_rise[1] = (int) Timer_Infrared_1_ReadCapture();
    updateSensorPos(1);
}

CY_ISR(inter_infrared_falling_1) {
    char strbuffer[15];
    inf_fall[1] = (int) Timer_Infrared_1_ReadCapture();
    n_fallingEdges[1] += 1;
    
    sprintf(strbuffer, "%i", n_fallingEdges[1]);
    LCD_Position(0,7);
    LCD_PrintString(strbuffer);
}

// 3
CY_ISR(inter_infrared_rising_2) {
    inf_rise_prev[2] = inf_rise[2];
    inf_rise[2] = (int) Timer_Infrared_2_ReadCapture();
    updateSensorPos(2);
}

CY_ISR(inter_infrared_falling_2) {
    char strbuffer[15];
    inf_fall[2] = (int) Timer_Infrared_2_ReadCapture();
    n_fallingEdges[2] += 1;
    
    sprintf(strbuffer, "%i", n_fallingEdges[2]);
    LCD_Position(1,0);
    LCD_PrintString(strbuffer);
}

// 4
CY_ISR(inter_infrared_rising_3) {
    inf_rise_prev[3] = inf_rise[3];
    inf_rise[3] = (int) Timer_Infrared_3_ReadCapture();
    updateSensorPos(3);
}

CY_ISR(inter_infrared_falling_3) {
    char strbuffer[15];
    inf_fall[3] = (int) Timer_Infrared_3_ReadCapture();
    n_fallingEdges[3] += 1;
    
    sprintf(strbuffer, "%i", n_fallingEdges[3]);
    LCD_Position(1,7);
    LCD_PrintString(strbuffer);
}

/*
static void printSensorPos(int id) {
    char strbuffer[15];
    //int clk = 24000;
    
    //double dx = (double) inf_dx[id] / clk;
    //double dy = (double) inf_dy[id] / clk;
    
    if (id == 0) {
        sprintf(strbuffer, "%.1f", inf_dx[id]);
        LCD_Position(0,0);
        LCD_PrintString(strbuffer);
        
        sprintf(strbuffer, "%.1f", inf_dy[id]);
        LCD_Position(1,0);
        LCD_PrintString(strbuffer);
        
    }
    else if (id == 1) {
        sprintf(strbuffer, "%.1f", inf_dx[id]);
        LCD_Position(0,4);
        LCD_PrintString(strbuffer);
        
        sprintf(strbuffer, "%.1f", inf_dy[id]);
        LCD_Position(1,4);
        LCD_PrintString(strbuffer);
    }
    else if (id == 2) {
        sprintf(strbuffer, "%.1f", inf_dx[id]);
        LCD_Position(0,8);
        LCD_PrintString(strbuffer);
        
        sprintf(strbuffer, "%.1f", inf_dy[id]);
        LCD_Position(1,8);
        LCD_PrintString(strbuffer);
    }
    else if (id == 3) {
        sprintf(strbuffer, "%.1f", inf_dx[id]);
        LCD_Position(0,12);
        LCD_PrintString(strbuffer);
        
        sprintf(strbuffer, "%.1f", inf_dy[id]);
        LCD_Position(1,12);
        LCD_PrintString(strbuffer);
    }
}*/

/*
int updateSensorOpt(int id) {
    if (xUpdated && yUpdated) return 1;
    
    //char strbuffer[15]; 
    if (risingEdge[id] != 1) return 0;
    risingEdge[id] = 0;
    
    int n_counts;
    if (inf_fall[id] > inf_rise[id]) {
        n_counts = inf_fall[id] - inf_rise[id];
    }
    else {
        n_counts = inf_fall[id] + (inf_timer_count - inf_rise[id]);
    }
    
    int sync_width = n_counts / 24;
    if (sync_width < 40) {
        int dt;
        if (inf_rise_prev[id] > inf_fall[id]) {
            dt = inf_rise_prev[id] - inf_fall[id];
        }
        else {
            dt = inf_rise_prev[id] + (inf_timer_count - inf_fall[id]);
        }
        
        if (xUpdated && axis[id] == 0) return 0;
        else if (yUpdated && axis[id] == 1) return 0;
        
        sendWireless(id, dt, axis[id]);
        if (axis[id] == 0) {
            xUpdated = 1;
        }
        else {
            yUpdated = 1;
        }
    }
    else if (abs(sync_width - 63) <= timing_tolerance) {
        skip = 0;
        axis[id] = 0;
    }
    else if (abs(sync_width - 73) <= timing_tolerance) {
        skip = 0;
        axis[id] = 1;
    }
    else if (abs(sync_width - 83) <= timing_tolerance) {
        skip = 0;
        axis[id] = 0;
    }
    else if (abs(sync_width - 94) <= timing_tolerance) {
        skip = 0;
        axis[id] = 1;
    }
    return 0;
}*/

void main() {   
    //char strbuffer[15];
    i = 0;
    j = 0;
    
    // initialize components
    CyGlobalIntEnable; // enable global interrupts
    inter_HE_Start();
    inter_HE_SetVector(inter_HE);
    
    // 1
    inter_infrared_rising_0_Start();
    inter_infrared_rising_0_SetVector(inter_infrared_rising_0);
    inter_infrared_falling_0_Start();
    inter_infrared_falling_0_SetVector(inter_infrared_falling_0);
    
    // 2
    inter_infrared_rising_1_Start();
    inter_infrared_rising_1_SetVector(inter_infrared_rising_1);
    inter_infrared_falling_1_Start();
    inter_infrared_falling_1_SetVector(inter_infrared_falling_1);
    
    // 3
    inter_infrared_rising_2_Start();
    inter_infrared_rising_2_SetVector(inter_infrared_rising_2);
    inter_infrared_falling_2_Start();
    inter_infrared_falling_2_SetVector(inter_infrared_falling_2);
    
    // 4
    inter_infrared_rising_3_Start();
    inter_infrared_rising_3_SetVector(inter_infrared_rising_3);
    inter_infrared_falling_3_Start();
    inter_infrared_falling_3_SetVector(inter_infrared_falling_3);
    
    PWM_Motor_Start();
    PWM_Servo_Start();
    
    Timer_HE_Start();
    Timer_Infrared_0_Start();
    Timer_Infrared_1_Start();
    Timer_Infrared_2_Start();
    Timer_Infrared_3_Start();
    
    Clock_Motor_Start();
    Clock_Servo_Start(); 
    Clock_Infrared_Start();
    
    UART_Start();
    LCD_Start();
    
    // initialize variables
    delta_t = 0;
    err_current = 0;
    error_sum = 0;
    output_initial = 60;
    output_current = output_initial;
    
    // initialize pid control variables
    kp = 30;
    ki = 10;
    
    speed = 0;
    
    /*---------------------infrared tracking----------------------------*/
    zeroIntArr(inf_rise, n_sensors);
    zeroIntArr(inf_rise_prev, n_sensors);
    zeroIntArr(inf_fall, n_sensors);
    zeroIntArr(risingEdge, n_sensors);
    zeroIntArr(axis, n_sensors);
    zeroIntArr(n_fallingEdges, n_sensors);
    
    skip = 0;
    inf_dbg = 0;
    dbg3 = 0;
    
    xUpdated = 0;
    yUpdated = 0;
    
    PWM_Motor_WriteCompare(output_initial);   // set initial PWM duty cycle
    previous_capture = (int) Timer_HE_ReadCapture();  // read initial capture count
    
    Control_Reg_Write(activate_0);
    for(;;)
    {   
        while (n_fallingEdges[0] < time_slice) {
        }
        sendWireless(0, dx[0], 0);
        sendWireless(0, dy[0], 1);
        n_fallingEdges[0] = 0;
 
        /*
        Control_Reg_Write(activate_0);
        n_fallingEdges[0] = 0;
        while (n_fallingEdges[0] < time_slice) {
        }
        sendWireless(0, dx[0], 0);
        sendWireless(0, dy[0], 1);*/
        
        /*
        Control_Reg_Write(activate_1);
        n_fallingEdges[0] = 0;
        while (n_fallingEdges[1] < time_slice) {
        }
        sendWireless(1, dx[1], 0);
        sendWireless(1, dy[1], 1);
        
        Control_Reg_Write(activate_2);
        n_fallingEdges[1] = 0;
        while (n_fallingEdges[2] < time_slice) {
        }
        sendWireless(2, dx[2], 0);
        sendWireless(2, dy[2], 1);*/
        
        //Timer_Infrared_1_ReadStatusRegister();
        //Control_Reg_Write(activate_3);
        //n_fallingEdges[2] = 0;
        //while (n_fallingEdges[3] < time_slice) {
        //}
        //sendWireless(3, dx[3], 0);
        //sendWireless(3, dy[3], 1);
        
        /*
        for (i = 0; i < n_sensors-1; i++) {
            if (dx[i] != 0) {
                sendWireless(i, dx[i], 0);
                dx[i] = 0;
            }
            if (dy[i] != 0) {
                sendWireless(i, dy[i], 1);
                dy[i] = 0;
            }
        }*/
        
        // 0
        /*
        int n_loop = 10;
        for (i = 0; i < n_loop; i++) {
            if (dx[0] != 0) {
                sendWireless(0, dx[0], 0);
                dx[0] = 0;
                break;
            }
        }
        
        for (i = 0; i < n_loop; i++) {
            if (dy[0] != 0) {
                sendWireless(0, dy[0], 1);
                dx[0] = 0;
                break;
            }
        }
        
        // 1
        for (i = 0; i < n_loop; i++) {
            if (dx[1] != 0) {
                sendWireless(1, dx[1], 0);
                dx[1] = 0;
                break;
            }
        }
        
        for (i = 0; i < n_loop; i++) {
            if (dy[1] != 0) {
                sendWireless(1, dy[1], 1);
                dy[1] = 0;
                break;
            }
        }
        
        // 2
        for (i = 0; i < n_loop; i++) {
            if (dx[2] != 0) {
                sendWireless(2, dx[2], 0);
                dx[2] = 0;
                break;
            }
        }
        
        for (i = 0; i < n_loop; i++) {
            if (dy[2] != 0) {
                sendWireless(2, dy[2], 1);
                dy[2] = 0;
                break;
            }
        }*/
        /*
        for (i = 0; i < n_sensors; i++) {
            updateSensorPos(i);
        }
        for (i = 0; i < n_sensors-1; i++) {
            if (!updateSensorOpt(i)) {
                i--;
            }
            else {
                xUpdated = 0;
                yUpdated = 0;
            }
        }*/
    }
}

/* [] END OF FILE */
