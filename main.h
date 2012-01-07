float fps=10000;
struct timeval tv;
unsigned int normaltime,tick;

#define NUM_TRAINS 10

int zone[9],state[NUM_TRAINS],oldstate[NUM_TRAINS];
float x=0,y=0,train[NUM_TRAINS][2],speedc=0.0001,speed[NUM_TRAINS];

float width=800,height=800;


void singals(){
	//allowance
	if(zone[1]!=1){
		if(zone[0]==2)
			zone[0]=0;
		if(zone[2]==2)
			zone[2]=0;
		if(zone[3]==2)
			zone[3]=0;
		if(zone[4]==2)
			zone[4]=0;
		if(zone[6]!=1 && zone[5]==2)
			zone[5]=0;
	}
	if(zone[0]!=1 && zone[2]!=1 && zone[3]!=1 && zone[4]!=1 && zone[5]!=1)
		if(zone[1]==2)
			zone[1]=0;
	if(zone[5]!=1 && zone[7]!=1 && zone[8]!=1)
		if(zone[6]==2)
			zone[6]=0;
	if(zone[6]!=1){
		if(zone[7]==2)
			zone[7]=0;
		if(zone[8]==2)
			zone[8]=0;
	}

	//prohibition
	if(zone[0]==1 && !zone[1])
		zone[1]=2;
	if(zone[1]==1){
		if(!zone[0])
			zone[0]=2;
		if(!zone[2])
			zone[2]=2;
		if(!zone[3])
			zone[3]=2;
		if(!zone[4])
			zone[4]=2;
		if(!zone[5])
			zone[5]=2;
	}
	if(zone[2]==1 && !zone[1])
		zone[1]=2;
	if(zone[3]==1 && !zone[1])
		zone[1]=2;
	if(zone[4]==1 && !zone[1])
		zone[1]=2;
	if(zone[5]==1){
		if(!zone[1])
			zone[1]=2;
		if(!zone[6])
			zone[6]=2;
	}
	if(zone[6]==1){
		 if(!zone[5])
			zone[5]=2;
		 if(!zone[7])
			zone[7]=2;
		 if(!zone[8])
			zone[8]=2;
	}
	if(zone[7]==1 && !zone[6])
		zone[6]=2;
	if(zone[8]==1 && !zone[6])
		zone[6]=2;
}

void graph()
{
	glBegin(3);

	if(zone[0]==1)
		glColor3ub(255,0,0);
	else if(zone[0]==2)
		glColor3ub(255,255,0);
	else
		glColor3ub(0,255,0);
	glVertex2f(-0.9,1);
	glVertex2f(-0.9,0.9);
	glVertex2f(0.6,0.9);
	glEnd();

	glBegin(1);
	if(zone[1]==1)
		glColor3ub(255,0,0);
	else if(zone[1]==2)
		glColor3ub(255,255,0);
	else
		glColor3ub(0,255,0);
	glVertex2f(0.6,0.9);
	glVertex2f(0.8,0.9);
	glVertex2f(0.7,1);
	glVertex2f(0.7,0.7);
	glVertex2f(0.6,0.8);
	glVertex2f(0.8,0.8);
	glEnd();

	glBegin(3);
	if(zone[2]==1)
		glColor3ub(255,0,0);
	else if(zone[2]==2)
		glColor3ub(255,255,0);
	else
		glColor3ub(0,255,0);
	glVertex2f(0.8,0.9);
	glVertex2f(0.9,0.9);
	glVertex2f(0.9,-0.9);
	glVertex2f(1,-0.9);
	glEnd();
	glBegin(1);
	if(zone[3]==1)
		glColor3ub(255,0,0);
	else if(zone[3]==2)
		glColor3ub(255,255,0);
	else
		glColor3ub(0,255,0);
	glVertex2f(0.8,-1);
	glVertex2f(0.8,0.8);
	glEnd();
	glBegin(1);
	if(zone[4]==1)
		glColor3ub(255,0,0);
	else if(zone[4]==2)
		glColor3ub(255,255,0);
	else
		glColor3ub(0,255,0);
	glVertex2f(0.7,-1);
	glVertex2f(0.7,0.7);
	glEnd();
	glBegin(1);
	if(zone[5]==1)
		glColor3ub(255,0,0);
	else if(zone[5]==2)
		glColor3ub(255,255,0);
	else
		glColor3ub(0,255,0);
	glVertex2f(0.6,0.6);
	glVertex2f(0.6,0.8);
	glEnd();
	glBegin(1);
	if(zone[6]==1)
		glColor3ub(255,0,0);
	else if(zone[6]==2)
		glColor3ub(255,255,0);
	else
		glColor3ub(0,255,0);
	glVertex2f(0.5,0.5);
	glVertex2f(0.6,0.5);
	glVertex2f(0.6,0.4);
	glVertex2f(0.6,0.6);
	glEnd();
	glBegin(1);
	if(zone[7]==1)
		glColor3ub(255,0,0);
	else if(zone[7]==2)
		glColor3ub(255,255,0);
	else
		glColor3ub(0,255,0);
	glVertex2f(0.6,-1);
	glVertex2f(0.6,0.4);
	glEnd();
	glBegin(1);
	if(zone[8]==1)
		glColor3ub(255,0,0);
	else if(zone[8]==2)
		glColor3ub(255,255,0);
	else
		glColor3ub(0,255,0);
	glVertex2f(0.5,-1);
	glVertex2f(0.5,0.5);
	glEnd();

	glBegin(1);
	glColor3ub(255,255,255);
	glVertex2f(0.6,0.9);
	glVertex2f(0.6,0.89);

	glVertex2f(0.8,0.9);
	glVertex2f(0.8,0.89);

	glVertex2f(0.6,0.8);
	glVertex2f(0.59,0.81);

	glVertex2f(0.8,0.8);
	glVertex2f(0.79,0.79);

	glVertex2f(0.7,0.7);
	glVertex2f(0.69,0.7);

	glVertex2f(0.6,0.6);
	glVertex2f(0.59,0.6);

	glVertex2f(0.5,0.5);
	glVertex2f(0.49,0.51);

	glVertex2f(0.6,0.4);
	glVertex2f(0.59,0.4);
	glEnd();

}

void drawtrain(){
	int i,rnd;

	for(i=0;i<NUM_TRAINS;i++){
		if(!state[i] && zone[0]!=1){
			state[i]=1;
			break;
		}
	}
	for(i=0;i<NUM_TRAINS;i++){
//		oldstate[i]=state[i];
//		if(!state[i]){
			glBegin(7);
			glColor3ub(255,255,255);
			glVertex2f(train[i][0]-0.005,train[i][1]-0.005);
			glVertex2f(train[i][0]+0.005,train[i][1]-0.005);
			glVertex2f(train[i][0]+0.005,train[i][1]+0.005);
			glVertex2f(train[i][0]-0.005,train[i][1]+0.005);
			glEnd();
//		}
		switch(state[i]){
		case 1:
			train[i][0]=-0.9;
			train[i][1]-=speed[i];
			if(train[i][1]<=0.9)
				state[i]=2;
			zone[0]=1;
		break;
		case 2:
			train[i][1]=0.9;
			train[i][0]+=speed[i];
			if(train[i][0]>=0.6){
				if(zone[1]!=1){
					zone[1]=1;
					zone[0]=0;
					speed[i]=speedc;
					state[i]=3;
				}else{
					speed[i]=0;
				}
			}
		break;
		case 3:
			train[i][1]=0.9;
			train[i][0]+=speed[i];
			if(train[i][0]>=0.7){
				rnd=random();
				if(rnd%3==0)
					state[i]=8; //varies: 8,4,9
				else if(rnd%3==1)
					state[i]=4;
				else
					state[i]=9;
			}
		break;
		case 4:
			train[i][1]=0.9;
			train[i][0]+=speed[i];
			if(train[i][0]>0.8){
				if(zone[2]!=1){
					zone[1]=0;
					zone[2]=1;
					speed[i]=speedc;
					state[i]=5;
				}else{
					speed[i]=0;
				}
			}
		break;
		case 5:
			train[i][1]=0.9;
			train[i][0]+=speed[i];
			if(train[i][0]>=0.9)
				state[i]=6;
		break;
		case 6:
			train[i][0]=0.9;
			train[i][1]-=speed[i];
			if(train[i][1]<=-0.9)
				state[i]=7;
		break;
		case 7:
			train[i][1]=-0.9;
			train[i][0]+=speed[i];
			if(train[i][0]>=1){
				state[i]=0;
				zone[2]=0;
			}
		break;
		case 8:
			train[i][0]=0.7;
			train[i][1]+=speed[i];
			if(train[i][1]>=1){
				state[i]=0;
				zone[1]=0;
			}
		break;
		case 9:
			train[i][0]=0.7;
			train[i][1]-=speed[i];
			if(train[i][1]<=0.8){
				rnd=random();
				if(rnd%3==0)
					state[i]=10; //varies: 10,11,12
				else if(rnd%3==1)
					state[i]=11;
				else
					state[i]=12;
			}
		break;
		case 10:
			train[i][1]=0.8;
			train[i][0]-=speed[i];
			if(train[i][0]<=0.6){
				if(zone[5]!=1){
					zone[5]=1;
					zone[1]=0;
					speed[i]=speedc;
					state[i]=13;
				}else{
					speed[i]=0;
				}
			}
		break;

		case 11:
			train[i][1]=0.8;
			train[i][0]+=speed[i];
			if(train[i][0]>=0.8){
				if(zone[3]!=1){
					zone[1]=0;
					zone[3]=1;
					speed[i]=speedc;
					state[i]=20;
				}else{
					speed[i]=0;
				}
			}
		break;
		case 12:
			train[i][0]=0.7;
			train[i][1]-=speed[i];
			if(train[i][1]<=0.7){
				if(zone[4]!=1){
					zone[1]=0;
					zone[4]=1;
					speed[i]=speedc;
					state[i]=19;
				}else{
					speed[i]=0;
				}
			}
		break;
		case 13:
			train[i][0]=0.6;
			train[i][1]-=speed[i];
			if(train[i][1]<=0.6){
				if(zone[6]!=1){
					zone[5]=0;
					zone[6]=1;
					speed[i]=speedc;
					state[i]=14;
				}else{
					speed[i]=0;
				}
			}
		break;
		case 14:
			train[i][0]=0.6;
			train[i][1]-=speed[i];
			if(train[i][1]<=0.5){
				rnd=random();
				if(rnd%2==0)
					state[i]=15; //varies: 15,16
				else
					state[i]=16;
			}
		break;
		case 15:
			train[i][1]=0.5;
			train[i][0]-=speed[i];
			if(train[i][0]<=0.5){
				if(zone[8]!=1){
					zone[6]=0;
					zone[8]=1;
					speed[i]=speedc;
					state[i]=17;
				}else{
					speed[i]=0;
				}
			}
		break;
		case 16:
			train[i][0]=0.6;
			train[i][1]-=speed[i];
			if(train[i][1]<=0.4){
				if(zone[7]!=1){
					zone[6]=0;
					zone[7]=1;
					speed[i]=speedc;
					state[i]=18;
				}else{
					speed[i]=0;
				}
			}
		break;
		case 17:
			train[i][0]=0.5;
			train[i][1]-=speed[i];
			if(train[i][1]<=-1){
				zone[8]=0;
				state[i]=0;
			}
		break;
		case 18:
			train[i][0]=0.6;
			train[i][1]-=speed[i];
			if(train[i][1]<=-1){
				zone[7]=0;
				state[i]=0;
			}
		break;
		case 19:
			train[i][0]=0.7;
			train[i][1]-=speed[i];
			if(train[i][1]<=-1){
				zone[4]=0;
				state[i]=0;
			}
		break;
		case 20:
			train[i][0]=0.8;
			train[i][1]-=speed[i];
			if(train[i][1]<=-1){
				zone[3]=0;
				state[i]=0;
			}
		break;
//reverse (+1000). still not done protection against deadlocks
/*
		case 1001:
			train[i][0]=-0.9;
			train[i][1]+=speed[i];
			if(train[i][1]>=1)
				state[i]=0;
		break;
		case 1002:
			train[i][1]=0.9;
			train[i][0]-=speed[i];
			if(train[i][0]<=-0.9)
				state[i]=1001;
		break;
		case 1003:
			train[i][0]=0.7;
			train[i][1]-=speed[i];
			if(train[i][1]<=0.9)
				state[i]=7; //varies: 4,7,1002
		break;
		case 1004:
			train[i][1]=0.9;
			train[i][0]-=speed[i];
			if(train[i][0]<=0.7)
				state[i]=7; //varies: 3,1002,7
		break;
		case 1005:
			train[i][0]=0.9;
			train[i][1]+=speed[i];
			if(train[i][1]>=0.9)
				state[i]=1004;
		break;
		case 1006:
			train[i][1]=-0.9;
			train[i][0]-=speed[i];
			if(train[i][0]<=0.9)
				state[i]=1005;
		break;
		case 1007:
			train[i][0]=0.7;
			train[i][1]+=speed[i];
			if(train[i][1]>=0.9)
				state[i]=4; //varies: 1002,3,4
		break;
		case 1008:
			train[i][1]=0.8;
			train[i][0]+=speed[i];
			if(train[i][0]>=0.7)
				state[i]=9; //varies: 1007,9,14
		break;
		case 1009:
			train[i][1]=0.8;
			train[i][0]-=speed[i];
			if(train[i][0]<=0.7)
				state[i]=8; //varies: 1007,8,14
		break;
		case 1010:
			train[i][0]=0.6;
			train[i][1]+=speed[i];
			if(train[i][1]>=0.8)
				state[i]=1008;
		break;
		case 1011:
			train[i][1]=0.5;
			train[i][0]+=speed[i];
			if(train[i][0]>=0.6)
				state[i]=1010; //varies: 1010,13
		break;
		case 1012:
			train[i][0]=0.5;
			train[i][1]+=speed[i];
			if(train[i][1]>=0.5)
				state[i]=1011;
		break;
		case 1013:
			train[i][0]=0.6;
			train[i][1]+=speed[i];
			if(train[i][1]>=0.5)
				state[i]=1010; //varies: 11,1010
		break;
		case 1014:
			train[i][0]=0.7;
			train[i][1]+=speed[i];
			if(train[i][1]>=0.8)
				state[i]=8; //varies: 8,1007,9
		break;
		case 1015:
			train[i][0]=0.8;
			train[i][1]+=speed[i];
			if(train[i][1]>=0.8)
				state[i]=1009;
		break;
*/
		default: //0
			train[i][0]=-0.9;
			train[i][1]=1;
		}
	}
}

