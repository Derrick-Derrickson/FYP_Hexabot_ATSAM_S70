/*
* Gait.c
*
* Created: 14/08/2016 11:44:45 PM
*  Author: to300
*/
#include "Gait.h"
#define STAND_UP_START_HGT 75
#define STAND_UP_TIME 30.00
//Stand up
void standUp( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk) {
	xzS[0] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,1,0);
	xzS[1] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,0,0);
	xzS[2] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,1,0);
	xzS[3] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,0,0);
	xzS[4] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,1,0);
	xzS[5] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,0,0);

	Ang[0] = legAngCalc(xzS[0].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((float)hexabot_walk->i/STAND_UP_TIME) ,xzS[0].Z);
	Ang[1] = legAngCalc(xzS[1].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((float)hexabot_walk->i/STAND_UP_TIME) ,xzS[1].Z);
	Ang[2] = legAngCalc(xzS[2].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((float)hexabot_walk->i/STAND_UP_TIME) ,xzS[2].Z);
	Ang[3] = legAngCalc(xzS[3].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((float)hexabot_walk->i/STAND_UP_TIME) ,xzS[3].Z);
	Ang[4] = legAngCalc(xzS[4].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((float)hexabot_walk->i/STAND_UP_TIME) ,xzS[4].Z);
	Ang[5] = legAngCalc(xzS[5].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((float)hexabot_walk->i/STAND_UP_TIME) ,xzS[5].Z);
	
	writeLegOut(0,Ang[0].S1,Ang[0].S2,Ang[0].S3);
	writeLegOut(1,Ang[1].S1,Ang[1].S2,Ang[1].S3);
	writeLegOut(2,Ang[2].S1,Ang[2].S2,Ang[2].S3);
	writeLegOut(3,Ang[3].S1,Ang[3].S2,Ang[3].S3);
	writeLegOut(4,Ang[4].S1,Ang[4].S2,Ang[4].S3);
	writeLegOut(5,Ang[5].S1,Ang[5].S2,Ang[5].S3);
}

void sitDown( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk) {
	xzS[0] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,1,0);
	xzS[1] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,0,0);
	xzS[2] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,1,0);
	xzS[3] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,0,0);
	xzS[4] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,1,0);
	xzS[5] = calcRotation(hexabot_walk->stance, 0, hexabot_walk->stance, 0, 0,0,0);

	Ang[0] = legAngCalc(xzS[0].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((STAND_UP_TIME-(float)hexabot_walk->i)/STAND_UP_TIME) ,xzS[0].Z);
	Ang[1] = legAngCalc(xzS[1].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((STAND_UP_TIME-(float)hexabot_walk->i)/STAND_UP_TIME) ,xzS[1].Z);
	Ang[2] = legAngCalc(xzS[2].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((STAND_UP_TIME-(float)hexabot_walk->i)/STAND_UP_TIME) ,xzS[2].Z);
	Ang[3] = legAngCalc(xzS[3].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((STAND_UP_TIME-(float)hexabot_walk->i)/STAND_UP_TIME) ,xzS[3].Z);
	Ang[4] = legAngCalc(xzS[4].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((STAND_UP_TIME-(float)hexabot_walk->i)/STAND_UP_TIME) ,xzS[4].Z);
	Ang[5] = legAngCalc(xzS[5].X, STAND_UP_START_HGT+(-hexabot_walk->hgt-STAND_UP_START_HGT)*((STAND_UP_TIME-(float)hexabot_walk->i)/STAND_UP_TIME) ,xzS[5].Z);
	
	writeLegOut(0,Ang[0].S1,Ang[0].S2,Ang[0].S3);
	writeLegOut(1,Ang[1].S1,Ang[1].S2,Ang[1].S3);
	writeLegOut(2,Ang[2].S1,Ang[2].S2,Ang[2].S3);
	writeLegOut(3,Ang[3].S1,Ang[3].S2,Ang[3].S3);
	writeLegOut(4,Ang[4].S1,Ang[4].S2,Ang[4].S3);
	writeLegOut(5,Ang[5].S1,Ang[5].S2,Ang[5].S3);
}

//default, sinusoid based paten
void Gait0( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk) {

	ofst[0] = ((float)hexabot_walk->i+(0*(hexabot_walk->Hexabot_leg_cycle_t/6)))/(hexabot_walk->Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[1] = ((float)hexabot_walk->i+(1*(hexabot_walk->Hexabot_leg_cycle_t/6)))/(hexabot_walk->Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[2] = ((float)hexabot_walk->i+(2*(hexabot_walk->Hexabot_leg_cycle_t/6)))/(hexabot_walk->Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[3] = ((float)hexabot_walk->i+(3*(hexabot_walk->Hexabot_leg_cycle_t/6)))/(hexabot_walk->Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[4] = ((float)hexabot_walk->i+(4*(hexabot_walk->Hexabot_leg_cycle_t/6)))/(hexabot_walk->Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[5] = ((float)hexabot_walk->i+(5*(hexabot_walk->Hexabot_leg_cycle_t/6)))/(hexabot_walk->Hexabot_leg_cycle_t)*2.0*M_PI;
	
	xzS[0] = calcRotation(hexabot_walk->stance, hexabot_walk->stride*cos(ofst[0]), hexabot_walk->stance, 0, hexabot_walk->movDir,1,hexabot_walk->movTurn);
	xzS[1] = calcRotation(hexabot_walk->stance, hexabot_walk->stride*cos(ofst[1]), hexabot_walk->stance, 0, hexabot_walk->movDir,0,hexabot_walk->movTurn);
	xzS[2] = calcRotation(hexabot_walk->stance, hexabot_walk->stride*cos(ofst[2]), hexabot_walk->stance, 0, hexabot_walk->movDir,1,hexabot_walk->movTurn);
	xzS[3] = calcRotation(hexabot_walk->stance, hexabot_walk->stride*cos(ofst[3]), hexabot_walk->stance, 0, hexabot_walk->movDir,0,hexabot_walk->movTurn);
	xzS[4] = calcRotation(hexabot_walk->stance, hexabot_walk->stride*cos(ofst[4]), hexabot_walk->stance, 0, hexabot_walk->movDir,1,hexabot_walk->movTurn);
	xzS[5] = calcRotation(hexabot_walk->stance, hexabot_walk->stride*cos(ofst[5]), hexabot_walk->stance, 0, hexabot_walk->movDir,0,hexabot_walk->movTurn);

	Ang[0] = legAngCalc(xzS[0].X,  (sin(ofst[0]) < 0)?-hexabot_walk->hgt:(hexabot_walk->pup*sin(ofst[0])-hexabot_walk->hgt)  ,xzS[0].Z);
	Ang[1] = legAngCalc(xzS[1].X,  (sin(ofst[1]) < 0)?-hexabot_walk->hgt:(hexabot_walk->pup*sin(ofst[1])-hexabot_walk->hgt)  ,xzS[1].Z);
	Ang[2] = legAngCalc(xzS[2].X,  (sin(ofst[2]) < 0)?-hexabot_walk->hgt:(hexabot_walk->pup*sin(ofst[2])-hexabot_walk->hgt)  ,xzS[2].Z);
	Ang[3] = legAngCalc(xzS[3].X,  (sin(ofst[3]) < 0)?-hexabot_walk->hgt:(hexabot_walk->pup*sin(ofst[3])-hexabot_walk->hgt)  ,xzS[3].Z);
	Ang[4] = legAngCalc(xzS[4].X,  (sin(ofst[4]) < 0)?-hexabot_walk->hgt:(hexabot_walk->pup*sin(ofst[4])-hexabot_walk->hgt)  ,xzS[4].Z);
	Ang[5] = legAngCalc(xzS[5].X,  (sin(ofst[5]) < 0)?-hexabot_walk->hgt:(hexabot_walk->pup*sin(ofst[5])-hexabot_walk->hgt)  ,xzS[5].Z);
	
}

//Second gait function
//Shannon its pretty

void Gait1( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk) {
	float grad = (float)(2.40 * (double)((*hexabot_walk).stride));
	float grad2 = (float)(12.00 * (double)((*hexabot_walk).stride));
	
	for(int i = 0; i < 6; i++) {
		//calculate the cycling offset
		ofst[i] = fmod( (float)(hexabot_walk->i + i*(float)hexabot_walk->Hexabot_leg_cycle_t/6.00) , ((float)hexabot_walk->Hexabot_leg_cycle_t))/(float)hexabot_walk->Hexabot_leg_cycle_t;
		//Calculate X and Z locations
		
		if( ofst[i] < (5.00/6.00) ) {
			xzS[i] = calcRotation((float)hexabot_walk->stance,  ( -(float)(hexabot_walk->stride) + (float)(grad*ofst[i]) )  , hexabot_walk->stance, 0, hexabot_walk->movDir,(i%2 == 0)?0:1,hexabot_walk->movTurn);
			Ang[i] = legAngCalc(xzS[i].X,-hexabot_walk->hgt,xzS[i].Z);
		}
		else {
			xzS[i] = calcRotation((float)hexabot_walk->stance,( ((float)(hexabot_walk->stride) - (float)(grad2*(ofst[i] - 5.00/6.00))) ) , hexabot_walk->stance, 0, hexabot_walk->movDir,(i%2 == 0)?0:1,hexabot_walk->movTurn);
			Ang[i] = legAngCalc(xzS[i].X,(-hexabot_walk->hgt+hexabot_walk->pup),xzS[i].Z);
		}
		//Calcuate the required angles for XZ posistions!
	}
}

/* Naked lady because why not?
                             . ...
                         .''.' .    '.
                    . '' ".'.:I:.'..  '.
                  .'.:.:..,,:II:'.'.'.. '.
                .':.'.:.:I:.:II:'.'.'.'.. '.
              .'.'.'.'::.:.:.:I:'.'.'.'. .  '
             ..'.'.'.:.:I::.:II:.'..'.'..    .
            ..'.'':.:.::.:.::II::.'.'.'.'..   .
           ..'.'.'.:.::. .:::II:..'.'.'.'.'.   .
          .':.''.':'.'.'.:.:I:'.'.'.'.'.. '..  ..
          ':. '.':'. ..:.::.::.:.'..'  ':.'.'.. ..
         .:.:.':'.   '.:':I:.:.. .'.'.  ': .'.. . ..
         '..:.:'.   .:.II:.:..   . .:.'. '.. '. .  ..
        .. :.:.'.  .:.:I:.:. .  . ..:..:. :..':. .  '.
       .:. :.:.   .:.:I:.:. .    . ..:I::. :: ::  .. ..
       .. :'.'.:. .:.:I:'.        ..:.:I:. :: ::.   . '.
       '..:. .:.. .:II:'         ,,;IIIH.  ::. ':.      .
      .:.::'.:::..:.AII;,      .::",,  :I .::. ':.       .
      :..:'.:II:.:I:  ,,;'   ' .;:FBT"X:: ..:.. ':.    . .
     .. :':III:. :.:A"PBF;.  . .P,IP;;":: :I:..'::. .    ..
     . .:.:II: A.'.';,PP:" .  . ..'..' .: :.::. ':...  . ..
     . .: .:IIIH:.   ' '.' .  ... .    .:. :.:.. :...    .'
     . .I.::I:IIA.        ..   ...    ..::.'.'.'.: ..  . .
      .:II.'.':IA:.      ..    ..:.  . .:.: .''.'  ..  . .
     ..::I:,'.'::A:.  . .:'-, .-.:..  .:.::AA.. ..:.' .. .
      ':II:I:.  ':A:. ..:'   ''.. . : ..:::AHI: ..:..'.'.
     .':III.::.   'II:.:.,,;;;:::::". .:::AHV:: .::'' ..
     ..":IIHI::. .  "I:..":;,,,,;;". . .:AII:: :.:'  . .
     . . IIHHI:..'.'.'V::. ":;;;"   ...:AIIV:'.:.'  .. .
      . . :IIHI:. .:.:.V:.   ' ' . ...:HI:' .:: :. .  ..
      . .  ':IHII:: ::.IA..      .. .A .,,:::' .:.    .
      :.  ...'I:I:.: .,AHHA, . .'..AHIV::' . .  :     ..
      :. '.::::II:.I:.HIHHIHHHHHIHHIHV:'..:. .I.':. ..  '.
   . . .. '':::I:'.::IHHHHHHHHMHMHIHI. '.'.:IHI..  '  '  '.
    ':... .  ''" .::'.HMHI:HHHHMHHIHI. :IIHHII:. . . .    .
     :.:.. . ..::.' .IV".:I:IIIHIHHIH. .:IHI::'.': '..  .  .
   . .:.:: .. ::'.'.'..':.::I:I:IHHHIA.'.II.:...:' .' ... . '..
  '..::::' ...::'.IIHII:: .:.:..:..:III:.'::' .'    .    ..  . .
  '::.:' .''     .. :IIHI:.:.. ..: . .:I:"' ...:.:.  ..    .. ..
     .:..::I:.  . . . .IHII:.:'   .. ..".::.:II:.:. .  ...   . ..
  .. . .::.:.,,...-::II:.:'    . ...... . .. .:II:.::  ...  .. ..
   ..:.::.I .    . . .. .:. .... ...:.. . . ..:.::.   :..   . ..
    .'.::I:.      . .. ..:.... . ..... .. . ..::. .. .I:. ..' .
  .'':.: I.       . .. ..:.. .  . .. ..... .:. .:.. .:I.'.''..
  . .:::I:.       . . .. .:. .    .. ..  . ... .:.'.'I'  .  ...
  . ::.:I:..     . . . ....:. . .   .... ..   .:...:.:.:. ''.''
  '.'::'I:.       . .. ....:. .     .. . ..  ..'  .'.:..:..    '
        :. .     . .. .. .:.... .  .  .... ...   .  .:.:.:..    '.
        :.      .  . . .. .:.... . . ........       .:.:.::. .    .
        :. .     . . . . .. .::..:  . ..:.. .        ::.:.:.. .    .
        :.. .    . . .  . .. ..:.:  .. .. .:. ..     ':::.::.:. .   .
        ':.. .  . . . .. .. ...::' .. ..  . .:. .     V:I:::::.. .   :.
         ::. .  . .. .. ... .:.::  .. .  . .. .. .     VI:I:::::..   ''B
          :.. .   . .. ..:.. ..I:... . .  . .. ... .    VII:I:I:::. .'::
          ':.. . . . .. ..:..:.:I:.:. .  . .. . .:. .    VHIII:I::.:..':
           ::..   . . .. ..:..:.HI:. .      . . .... .   :HHIHIII:I::..:
           ':. .  . .. .. ..:.:.:HI:.    . . .. ..... .   HHHHIHII:I::.'
            :.. .  . . .. .:.:.:.HI:.      . . .. ... .   IHHHHIHHIHI:'
             :..  .  . . .. ..:..IH:.     . . .. .. ,,, . 'HHHHHHHHI:'
             ':..   . . .. ..:.:.:HI..   .  . .. . :::::.  MIH:"""'
              :. . .  . .. ..::.:.VI:.     . . .. .:::'::. HIH
               :..  .  . .. .:.:.:.V:.    . . . ...::I"A:. HHV
                :. .  .  . .. ..:.:.V:.     . . ....::I::'.HV:
                 :. .  . . . .. .:..II:.  . . . ....':::' AV.'
                  :.. . . .. ... .:..VI:. . . .. .:. ..:.AV'.
                  ':.. . .  .. ..:.:.:HAI:.:...:.:.:.:.AII:.
                   I:. .  .. ... .:.:.VHHII:..:.:..:A:'.:..
                   IA..  . . .. ..:.:.:VHHHHIHIHHIHI:'.::.
                   'HA:.  . . .. ..:.:.:HHHIHIHHHIHI:..:.
                    HIA: .  . . .. ...:.VHHHIHIIHI::.:...
                    HIHI:. .  .. ... .::.HHHIIHIIHI:::..
                    HII:.:.  .  .. ... .::VHHIHI:I::.:..
                    AI:..:..  .  . .. ..:.VHIII:I::.:. .
                   AI:. ..:..  .  . .. ..' VHIII:I;... .
                  AI:. .  .:.. .  .  . ...  VHIII::... .
                .A:. .      :.. .  . .. .:.. VHII::..  .
               A:. . .       ::. .. .. . .:.. "VHI::.. .
             .:.. .  .        :.. .:..... .::.. VHI:..
            ... . .  .     . . :.:. ..:. . .::.. VI:..  .
           .. .. .  .    . . ...:... . .. . .:::. V:..  .
          '.. ..  .   .  .. ..:::.... .:. . ..::.. V..  .
        . . .. . .   . . .. ..:::A. ..:. . . .::.. :..
       . .. .. .. . .  . ... ..::IA.. .. . .  ..::. :..  .
      .. .. ... . .  .. .... .:.::IA. . .. . ..:.::. :.  .
     . . . .. .   . . .. ..:..:.::IIA. . .  .. .:.::. :. .
    .. . .  .   . . .. ... ..:.::I:IHA. .  . . ..:.::. . .
   .: ..  .  .   . . ... .:.. .:I:IIHHA. .  . .. .::I:. .
  .::.  .     . . .. ..:. .::.:IIHIIHHHA.  .  .. ..:I:. . .
  A::..      .  .  ...:..:.::I:IHIHIHHHHA.  .  . ..::I:. .
 :HI:.. .       . .. .:.:.::I:IHIHIIHIHHHA. .   .. .::I:. ..
 AI:.. .. .    . .. .:.:.::II:IHIIIHIHIHHHA.  .  . ..::I:. ..
:HI:.. . .   .  . .. .::.:I:IHIHIIIHIHIIHHHA..  . .. .::I:. ..
AI:.:.. .  .  .  ... .::.::I:IHIIHIHIHIHIHIHHA. .  . ..::I:. .
HI:. .. . .  .  . .. .:..::IIHIHIHIIIIWHIIHHMWA.  . . .:::I:. . .
HI:.. . .  .   . .. ..:.::I:IIHHIIHIHIHIHHMMW"  '.. . ..:::II: . .
HI::.. .  .   .  .. .:..:::IIHIHIIWIWIIWMWW" .    .. . ..::III: .  .
HI::... . . .  . ... ..:.:::IIHIWIWIWMWMWW. .  .   . .. .:.:III. .   .
II::.:.. . .  .  .. ......:..IHWHIWWMWMW".. . . . . '... .:.:IHI:..    .
II:I::.. .  .   .  . .....::.:IHWMWWWMW:.. .  .  . .  .:..:::IIHII..
:II:.:.:.. .  .   . ......:.:.:IWWMWWW:.:.. .  .  .  . :...:.:IHHI:..
 HI::.:. . . .  .  . ...:.::.::.VWMWW::.:.:.. .  . .. . :.. ..:IHHI::.'-
 HII::.:.. .  .  . .. .:..:.'.  'WWWI::.::.:.. . .  . .. ':...:II:IIII::
 III::.:... .  .  . ...:.:... .   WII:I::.:.. .  .  .. . . :.:::...::.::
  VII::.:.. . . . .. ...:....      VHI:I::.:.. .  . ... .. .::.:..:.:..:
   VII::.:.. . .  . ..:.::.. .     :HHII:I::.:.. . . .. ..  .'::':......
   III:I::.. .. . . .. .:.:.. .    :VHIHI:I::.:... . . .. .. .':. .. .AH
  AA:II:I::.. . . .  .. ..:.. . .  ::HHIHII:I::.:... .. .. ... .:.::AHHH
 AHH:I:I::.:.. .  . .. ..:.:.. .   ::VHHHVHI:I::.:.:.. ..:. .::.A:.AHHHM
 HHHAII:I::.:.. . . . .. ..:.. . . :::HIHIHIHII:I::.:.. .. .:. ..AHHMMM:
AHHHH:II:I::.:.. . . .. ..:.:.. . .:I:MMIHHHIHII:I:::.:. ..:.:.AHHHMMM:M
HHHHHA:II:I::.. .. . . .. .:... . .:IIVMMMHIHHHIHII:I::. . .. AHHMMMM:MH
HHHHHHA:I:I:::.. . . . ... ..:.. ..:IHIVMMHHHHIHHHIHI:I::. . AHMMMMM:HHH
HHHHHMM:I::.:.. . . . .. ...:.:...:IIHHIMMHHHII:.:IHII::.  AHMMMMMM:HHHH
HHHHHMMA:I:.:.:.. . . . .. ..:.:..:IIHHIMMMHHII:...:::.:.AHMMMMMMM:HHHHH
HHHHHMMMA:I::... . . . . .. ..:.::.:IHHHIMMMHI:.:.. .::AHMMMMMMM:HHHHHHH
VHHHHMMMMA:I::.. . .  . . .. .:.::I:IHHHIMMMMHI:.. . AHMMMMMMMM:HHHHHHHH
 HHHMMMMMM:I:.:.. . .  . . ...:.:IIHIHHHIMMMMMHI:.AHMMMMMMMMM:HHHHHHHHHH
 HHHHMMMMMA:I:.:.. .  .  . .. .:IIHIHHHHIMMMMMH:AMMMMMMMMMMM:HHHHHHHHHHH
 VHHHMMMMMMA:I:::.:. . . . .. .:IHIHHHHHIMMMV"AMMMMMMMMMMMM:HHHHHHHHHHHH
  HHHHHMMMMMA:I::.. .. .  . ...:.:IHHHHHHIM"AMMMMMMMMMMMM:HHHHHHHHHHHHHH
  VHHHHHMMMMMA:I:.:.. . . .  .. .:IHIHHHHI:AMMMMMMMMMMMIHHHHHHHHHHHHHHHH
   VHHHHHMMMMMA:I::.:. . .  .. .:.:IHHHV:MMMMMIMMMMMMMMMMMMMHHHHHHHHV::.
    VHHHHMMMMMMA:::.:..:.. . .. .:::AMMMMMMMM:IIIIIHHHHHHHHHHHHHHHV:::..
     HHHHHMMMIIIA:I::.:.:..:... AMMMMMMMMMM:IIIIIIHHHHHHHHHHHHHHHV::::::
     VHHHHMMIIIIMA:I::::.::..AMMMMMMMMMMM:IIIIIIIHHHHHHHHHHHHHHV::::::::
      HHHHMIIIIMMMA:II:I::AIIIMMMMMMMMMM:IIIIIIIHHHHHHHHHHHHHHV:::::::::
      VHHHHIIIMMMMMMA:I:AIIIIIIMMMMMM:IIIIIIIIHHHHHHHHHHHHHHV::::::::"'
       HHHHHIIMMMMMMIMAAIIIIIIIIMMM:IIIIIIIIHHHHHHHHHHHHHHHV:::::""'
       VHHHIIIIMMMMIIIIIIIIIIIIII:IIIIIIIIHHHHHHHHHHHHHHHV::""'
        VHHIIIMMMMMIIIIIIIIIIIIIIIIIIIIIHHHHHHHHHHHHHHHV
         VHHIMMMMMMMIIIIIIIIIIIIIIIIIHHHHHHHHHHHHHV
          VHHHMMMMMMMMIIIIIIIIIIIHHHHHHHHHHHV
           VHHHMMMMMMMMMMMMMHHHHHHHHHHHHHV
*/