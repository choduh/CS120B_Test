//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i


unsigned char detected = 0;
/*complete the state machine*/

void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            //init variable(s) here.
	    if((PINA & 0xF8) == 0){
		detect_eq_state = noQuakeDet;
		}
	    else{
		detect_eq_state = QuakeDet;
		}
            break;
	case QuakeDet:
		detect_eq_state = DEQInit;
		break;
		
	case noQuakeDet:
		detect_eq_state = DEQInit;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;
	case QuakeDet:
		detected = 1;
		break;
	case noQuakeDet:
		detected = 0;
		break;
        default:
            break;
    }
}
