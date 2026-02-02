#include "son.h"


Son::Son(){
    TCCR0A = (0 << COM0A1)|(1 << COM0A0) |(0 << WGM01)|(1 << WGM00); // mode PWM phase correct
}


void Son::creerSon(uint8_t midiNote){
    DDRB |= (1 << PB3) | (1 << PB2);
    double frequence = 440.0 * pow(2.0, (midiNote - 69) / 12.0);
    if (frequence<400){
        ocrConstForce_=7650;
        TCCR0B = (1 << CS02)|(0 << CS01)|(0 << CS00)|(1 << WGM02);   // Prescaler de 256
    }
    else{
        ocrConstForce_=31000;
        TCCR0B = (0 << CS02)|(1 << CS01)|(1 << CS00)|(1 << WGM02);   // Prescaler de 64
    }
    OCR0A= ocrConstForce_/frequence; 
}



void Son::creerSonMegalovania(uint16_t frequence){
    DDRB |= (1 << PB3) | (1 << PB2);
    if (frequence<400){
        ocrConstForce_=7650;
        TCCR0B = (1 << CS02)|(0 << CS01)|(0 << CS00)|(1 << WGM02);   // Prescaler de 256
    }
    else{
        ocrConstForce_=31000;
        TCCR0B = (0 << CS02)|(1 << CS01)|(1 << CS00)|(1 << WGM02);   // Prescaler de 64
    }

    OCR0A= ocrConstForce_/frequence;
}


void Son::stopSon(){
    DDRB = (0 << PB3) | (0 << PB2);
}


void Son::jouerMegalovania(){
//     for (int i =1; i<2;i++){
//     //mesure 1
//         creerSonMegalovania(146);  // Re 2
//         _delay_ms(DUREE_DOUBLE_CROCHE); 
        
//         stopSon();
//         _delay_ms(5);     
        
//         creerSonMegalovania(146);  // Re 2
//         _delay_ms(124);     
        
//         stopSon();
//         _delay_ms(2);   
        
//         creerSonMegalovania(298);  // Re 3
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         creerSonMegalovania(220);  // La 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         stopSon();
//         _delay_ms(DUREE_CROCHE);
        
//         creerSonMegalovania(207);  //Sol# 2
//         _delay_ms(DUREE_DOUBLE_CROCHE); 
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         creerSonMegalovania(196);  // Sol 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);      
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);

//         creerSonMegalovania(175);  //Fa 2
//         _delay_ms(DUREE_CROCHE);
        
//         stopSon();
//         _delay_ms(2);     
        
//         creerSonMegalovania(146);  // Re 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);     
            
//         stopSon();
//         _delay_ms(2);      
        
//         creerSonMegalovania(175);  //Fa 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);
            
//         stopSon();
//         _delay_ms(2);
        
//         creerSonMegalovania(196);  // Sol 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);


//     // mesure 2



//         creerSonMegalovania(130);  // Do 2
//         _delay_ms(DUREE_DOUBLE_CROCHE); 
        
//         stopSon();
//         _delay_ms(5);     
        
//         creerSonMegalovania(130);  // Do 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);     
        
//         stopSon();
//         _delay_ms(2);   
        
//         creerSonMegalovania(298);  // Re 3
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         creerSonMegalovania(220);  // La 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         stopSon();
//         _delay_ms(DUREE_CROCHE);
        
//         creerSonMegalovania(207);  //Sol# 2
//         _delay_ms(DUREE_DOUBLE_CROCHE); 
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         creerSonMegalovania(196);  // Sol 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);      
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);

//         creerSonMegalovania(175);  //Fa 2
//         _delay_ms(DUREE_CROCHE);
        
//         stopSon();
//         _delay_ms(2);     
        
//         creerSonMegalovania(146);  // Re 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);     
            
//         stopSon();
//         _delay_ms(2);      
        
//         creerSonMegalovania(175);  //Fa 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);
            
//         stopSon();
//         _delay_ms(2);
        
//         creerSonMegalovania(196);  // Sol 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         stopSon();
//         _delay_ms(2);

//     //mesure 3

//         creerSonMegalovania(123);  // Si 1
//         _delay_ms(DUREE_DOUBLE_CROCHE); 
        
//         stopSon();
//         _delay_ms(5);     
        
//         creerSonMegalovania(123);  // Si 1
//         _delay_ms(124);     
        
//         stopSon();
//         _delay_ms(2);   
        
//         creerSonMegalovania(298);  // Re 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         creerSonMegalovania(220);  // La 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         stopSon();
//         _delay_ms(DUREE_CROCHE);
        
//         creerSonMegalovania(207);  //Sol# 1
//         _delay_ms(DUREE_DOUBLE_CROCHE); 
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         creerSonMegalovania(196);  // Sol 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);      
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);

//         creerSonMegalovania(175);  //Fa 1
//         _delay_ms(DUREE_CROCHE);
        
//         stopSon();
//         _delay_ms(2);     
        
//         creerSonMegalovania(146);  // Re 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);     
            
//         stopSon();
//         _delay_ms(2);      
        
//         creerSonMegalovania(175);  //Fa 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);
            
//         stopSon();
//         _delay_ms(2);
        
//         creerSonMegalovania(196);  // Sol 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);

//         stopSon();
//         _delay_ms(2);


//     //mesure 4

//         creerSonMegalovania(116);  // Sib 1
//         _delay_ms(DUREE_DOUBLE_CROCHE); 
        
//         stopSon();
//         _delay_ms(5);     
        
//         creerSonMegalovania(116);  // Sib 1
//         _delay_ms(124);     
        
//         stopSon();
//         _delay_ms(2);   
        
//         creerSonMegalovania(298);  // Re 2
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         creerSonMegalovania(220);  // La 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         stopSon();
//         _delay_ms(DUREE_CROCHE);
        
//         creerSonMegalovania(207);  //Sol# 1
//         _delay_ms(DUREE_DOUBLE_CROCHE); 
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);
        
//         creerSonMegalovania(196);  // Sol 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);      
        
//         stopSon();
//         _delay_ms(DUREE_DOUBLE_CROCHE);

//         creerSonMegalovania(175);  //Fa 1
//         _delay_ms(DUREE_CROCHE);
        
//         stopSon();
//         _delay_ms(2);     
        
//         creerSonMegalovania(146);  // Re 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);     
            
//         stopSon();
//         _delay_ms(2);      
        
//         creerSonMegalovania(175);  //Fa 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);
            
//         stopSon();
//         _delay_ms(2);
        
//         creerSonMegalovania(196);  // Sol 1
//         _delay_ms(DUREE_DOUBLE_CROCHE);

//         stopSon();
//         _delay_ms(2);
//     }

// // VERSE 1
// // MESURE 1
//    creerSonMegalovania(698.5);  //
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);     
    
//     creerSonMegalovania(698.5);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);     
    
//     stopSon();
//     _delay_ms(2);   
    
//     creerSonMegalovania(698.5);  // 
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(698.5);  // La 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(698.5);  //Sol# 1
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(587.33);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(10);

//     creerSonMegalovania(587.33);  //Fa 1
//     _delay_ms(2*DUREE_CROCHE+DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(2);

//     // mesure 2
//    creerSonMegalovania(698.5);  //
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);     
    
//     creerSonMegalovania(698.5);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);     
    
//     stopSon();
//     _delay_ms(2);   
    
//     creerSonMegalovania(698.5);  // 
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(784);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(830.61);  //Sol# 1                 698.5 =13, 830.61 = 16, 784 = 15
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_TRIPLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(830.61);  // Sol 1
//     _delay_ms(DUREE_TRIPLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_TRIPLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698.5);  // Sol 1
//     _delay_ms(DUREE_TRIPLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

    
//     creerSonMegalovania(587.33);  // Sol 1
//     _delay_ms(DUREE_TRIPLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(15);
    
//     creerSonMegalovania(698.5);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(9);

       
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);

// // mesure 3
//    creerSonMegalovania(698.5);  //
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);     
    
//     creerSonMegalovania(698.5);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);     
    
//     stopSon();
//     _delay_ms(2);   
    
//     creerSonMegalovania(698.5);  // 
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(784);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(830.61);  //Sol# 1                 698.5 =13, 830.61 = 16, 784 = 15
//     _delay_ms(DUREE_DOUBLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(1046.5);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(3*DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

// //mesure 4

//     creerSonMegalovania(1174.66);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);

    
//     creerSonMegalovania(1174.66);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(1174.66);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

       
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
       
//     creerSonMegalovania(1174.66);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
       
//     creerSonMegalovania(1046.5);  // Sol 1
//     _delay_ms(4*DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_TRIPLE_CROCHE);

// // mesure 5
//    creerSonMegalovania(880);  //
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);     
    
//     creerSonMegalovania(880);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);     
    
//     stopSon();
//     _delay_ms(2);   
    
//     creerSonMegalovania(880);  // 
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(880);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(880);  //Sol# 1                 698.5 =13, 830.61 = 16, 784 = 15
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE+2*DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(186);      
    
//     stopSon();
//     _delay_ms(2);

// // mesure 6
//    creerSonMegalovania(880);  //
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(5);     
    
//     creerSonMegalovania(880);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);     
    
//     stopSon();
//     _delay_ms(5);   
    
//     creerSonMegalovania(880);  // 
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(880);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(784);  //Sol# 1                 698.5 =13, 830.61 = 16, 784 = 15, 
//     _delay_ms(DUREE_DOUBLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(1174.66);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
        
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

// //mesure 7
//    creerSonMegalovania(1174.66);  //
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);     
    
//     creerSonMegalovania(880);  //
//     _delay_ms(DUREE_CROCHE);     
    
//     stopSon();
//     _delay_ms(2);   
    
//     creerSonMegalovania(784);  // 
//     _delay_ms(DUREE_CROCHE);
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698.5);  //
//     _delay_ms(DUREE_CROCHE);
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(1046.5);  //Sol# 1                 698.5 =13, 830.61 = 16, 784 = 15, 
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698.5);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(659);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

// //mesure 8
//    creerSonMegalovania(466);  //
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);     
    
//     creerSonMegalovania(523);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);     
    
//     stopSon();
//     _delay_ms(2);   
    
//     creerSonMegalovania(587);  // 
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(698.5);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(1046);  //Sol# 1        698.5 =13, 830.61 = 16, 784 = 15, 1046 = 20
//     _delay_ms(4*DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(4*DUREE_CROCHE+DUREE_TRIPLE_CROCHE);

// //Verse 2
// //mesure 1

//    creerSonMegalovania(698.5);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);     
    
//     creerSonMegalovania(587);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);     
    
//     stopSon();
//     _delay_ms(2);   
    
//     creerSonMegalovania(698.5);  // 
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  //
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(830);  //Sol# 1    698.5 =13, 830.61 = 16, 784 = 15, 1046 = 20, 1174 = 22
//     _delay_ms(DUREE_DOUBLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(587);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

// // mesure 2

//      creerSonMegalovania(830); 
//     _delay_ms(DUREE_TRIPLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_TRIPLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698);  // Sol 1
//     _delay_ms(DUREE_TRIPLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(587);  // Sol 1
//     _delay_ms(DUREE_TRIPLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698);  //Sol# 1    698.5 =13, 830.61 = 16, 784 = 15, 1046 = 20, 1174 = 22
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(2*DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(830);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

// // mesure 3

//      creerSonMegalovania(1046); 
//     _delay_ms(DUREE_DOUBLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(830);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698);  //Sol# 1    698.5 =13, 830.61 = 16, 784 = 15, 1046 = 20, 1174 = 22, 880=17
//     _delay_ms(DUREE_DOUBLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(587);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(659);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(1046);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

// // mesure 4

//      creerSonMegalovania(1120); 
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(830);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(830);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698);  //Sol# 1    698.5 =13, 830.61 = 16, 784 = 15, 1046 = 20, 1174 = 22, 880=17
//     _delay_ms(DUREE_DOUBLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(7*DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
// //mesure 5

//      creerSonMegalovania(349); 
//     _delay_ms(DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(392);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(440);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698);  // Sol 1
//     _delay_ms(DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(659);  //Sol# 1    698.5 =13, 830.61 = 16, 784 = 15, 1046 = 20, 1174 = 22, 880=17
//     _delay_ms(2*DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(587);  // Sol 1
//     _delay_ms(2*DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

// // mesure 6
//      creerSonMegalovania(659); 
//     _delay_ms(2*DUREE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698);  // Sol 1
//     _delay_ms(2*DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(2*DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(659);  // Sol 1   698.5 =13, 830.61 = 16, 784 = 15, 1046 = 20, 1174 = 22, 880=17
//     _delay_ms(2*DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
// //mesure 7

//      creerSonMegalovania(880); 
//     _delay_ms(7*DUREE_DOUBLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(DUREE_DOUBLE_CROCHE);
    
//     creerSonMegalovania(880);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(830);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(784);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(739);  //Sol# 1    698.5 =13, 830.61 = 16, 784 = 15, 1046 = 20, 1174 = 22, 880=17
//     _delay_ms(DUREE_DOUBLE_CROCHE); 
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(698);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(659);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);
    
//     creerSonMegalovania(622);  // Sol 1
//     _delay_ms(DUREE_DOUBLE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

// //mesure 8

//     creerSonMegalovania(587);  // Sol 1
//     _delay_ms(3*DUREE_CROCHE);      
    
//     for (int i = 587; i<660 ;++i){
//       creerSonMegalovania(i);  
//       _delay_ms(3.4);
//     }
//     stopSon();
//     _delay_ms(2);

//     creerSonMegalovania(660);  // Sol 1
//     _delay_ms(4*DUREE_CROCHE);      
    
//     stopSon();
//     _delay_ms(2);

}



