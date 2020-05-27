//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

unsigned char i =0;

unsigned char h = 1;
unsigned char l = 9;
/*complete the state machine*/

void Ping()
{
    switch(ping_state)
    {
        case PInit:
		if(i <= h){
			ping_state = Phigh;
		}
		else if(i <= l){
			ping_state = Plow;
		}
		
            break;
	case Phigh:
		ping_state = PInit;
		break;
	case Plow:
		ping_state = PInit;
		break;
	
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
		
            break;
	case Phigh:
		h = 1;
		i++;
		
		break;
	case Plow:
		l = 0;
		i++;
        default:
            break;
    }
}
