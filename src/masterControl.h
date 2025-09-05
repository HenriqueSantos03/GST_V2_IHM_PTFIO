#ifndef MASTER_CONTROL_H
#define MASTER_CONTROL_H

//*******************************************************************************************
// constantes
//*******************************************************************************************
//enum VAL_BTN_PERCENT{VAL_40PCT = 40, VAL_60PCT = 60, VAL_80PCT = 80, VAL_100PCT = 100, VAL_120PCT = 120}; 
enum PERCENTS_FASES{PERCENT_ALL,PERCENT_FASE_L1,PERCENT_FASE_L2, PERCENT_FASE_L3}; 
//Valores minimos e maximos do slider
#define SET_POINT_FREQ50_MIN 400      //Valores divididos por 10 
#define SET_POINT_FREQ50_MAX 600
#define SET_POINT_FREQ60_MIN 500
#define SET_POINT_FREQ60_MAX 700
#define SET_POINT_FREQCENT50 500
#define SET_POINT_FREQCENT60 600
//Valor maximo do setpoint das fases
#define VAL_MAX_SETPOINT_FASE 6000
//Valores dos checkbox de escala
#define VAL_CHECKBOX_ESCALA0 120
#define VAL_CHECKBOX_ESCALA1 240
#define VAL_CHECKBOX_ESCALA2 1100
#define VAL_CHECKBOX_ESCALA3 2200
#define VAL_CHECKBOX_ESCALA4 3800
#define VAL_CHECKBOX_ESCALA5 4400
#define VAL_CHECKBOX_ESCALA6 4800
#define VAL_CHECKBOX_ESCALA7 640

//Valores botões porcentagens
#define VAL_40PCT 40
#define VAL_60PCT 60
#define VAL_80PCT 80
#define VAL_100PCT 100
#define VAL_120PCT 120

//Status AC/DC e %/grandeza (v)                            
#define STATUS_TENSAO 1
#define STATUS_PERCENT 0 
//Multiplicador do SetPoint Maximo
#define SET_POINT_MAX_MULT 0.1275
#define SET_POINT_PERCENT_MAX 127.5
//Valores padrao incialização do programa

#define STATUS_PADRAO_HAB 0               //Determina o valor inicial das CBs que habilitam/desabilitam as fases
#define ESCALA_PADRAO 1100                //seletor de escala 
#define PASSO_PADRAO 5                    //seletor de passo
#define FREQ_PADRAO 600                   //Frequencia padrão (ALTERAR)
#define FREQ_SLIDER_PADRAO 600            //Frequencia padrão do slider (ALTERAR)
#define SETPOINT_L1 0
#define SETPOINT_L2 0
#define SETPOINT_L3 0
#define STATUS_GRUPO_FASES 1              //Determina o estado das fases (se estão ativas/inativas agrupadas/desgrupadas)
#define STATUS_L1 0                       
#define STATUS_L2 0
#define STATUS_L3 0
#define STATUS_ONOFF 0                //Determina o estado de on/off 

//Constantes para sequencia de fase
#define CONST_FASE_L1 1
#define CONST_FASE_L2 2
#define CONST_FASE_L3 3

#define TIME_REFRESH 250  //Tempo de refresh dos dados em ms
#define TIMEOUT_STATUS 20 //Timeout para aguardar resposta do status em ms

// Enum para a máquina de estados
enum MASTER_STATE {
    STATE_IDLE,         // Estado ocioso, aguardando início do ciclo
    STATE_SEND_REFRESH, // Envia comando de refresh
    STATE_WAIT_STATUS,  // Aguarda resposta do comando de status
    STATE_PROCESS_COMMAND // Processa a resposta recebida
};

typedef struct{
  bool statusOnOff;         //determina o status do On/Off
  bool modeVolt;            //determina se a checkbox de grandeza está em tensao (1) ou porcentagem (0)
  bool modeAcDc;            //determina se a saída está em AC (0) ou DC (1)
  bool atvL1;               //determina se a fase 1 está ativa 
  bool atvL2;               //determina se a fase 2 está ativa 
  bool atvL3;               //determina se a fase 3 está ativa 
  bool habL1;               //determina se a fase 1 está habilitada
  bool habL2;               //determina se a fase 2 está habilitada
  bool habL3;               //determina se a fase 3 está habilitada
  bool atvGrupoFases;       //Determina o estado do grupo de fases
  double vEscala;           //determina o valor selecionado na checkbox de escala (Vpadrao = 110Vac)
  uint8_t valPasso;          //valor do passo de incremento/decremento
  double freqSlider;        //Valor do objeto slider 
  double freqAt;            //Valor de frequencia atual
  double setPointL1;        //determina o valor atual (em volts) do setPoint da fase 1
  double setPointL2;        //determina o valor atual (em volts) do setPoint da fase 2
  double setPointL3;        //determina o valor atual (em volts) do setPoint da fase 3
  double setPointPercentL1; //Determina o valor atual (em porcentagem) do setPoint da fase 1
  double setPointPercentL2; //Determina o valor atual (em porcentagem) do setPoint da fase 2
  double setPointPercentL3; //Determina o valor atual (em porcentagem) do setPoint da fase 3
  double memSetPointL1;     //armazena o valor atual (em porcentagem) do setPoint da fase 1 quando o teclado for habilitado
  double memSetPointL2;     //armazena o valor atual (em porcentagem) do setPoint da fase 2 quando o teclado for habilitado
  double memSetPointL3;     //armazena o valor atual (em porcentagem) do setPoint da fase 3 quando o teclado for habilitado
  uint8_t outL1;            //Variavel que controla a fase L1 e permite a inversão de fase com outra
  uint8_t outL2;            //Variavel que controla a fase L2 e permite a inversão de fase com outra
  uint8_t outL3;            //Variavel que controla a fase L3 e permite a inversão de fase com outra
  uint16_t tensaoL1;       //Valor atual de tensão da fase 1
  uint16_t tensaoL2;       //Valor atual de tensão da fase 2
  uint16_t tensaoL3;       //Valor atual de tensão da fase 3
  uint16_t correnteL1;      //Valor atual de corrente da fase 1
  uint16_t correnteL2;      //Valor atual de corrente da fase 2
  uint16_t correnteL3;      //Valor atual de corrente da fase 3
  uint16_t correnteMaxL1;      //Valor maximo de corrente da fase 1 setado pela ihm
  uint16_t correnteMaxL2;      //Valor maximo de corrente da fase 2 setado pela ihm
  uint16_t correnteMaxL3;      //Valor maximo de corrente da fase 3 setado pela ihm
  uint16_t fatorDePotenciaL1;
  uint16_t fatorDePotenciaL2;
  uint16_t fatorDePotenciaL3;
  uint8_t statusPlacaL1;
  uint8_t statusPlacaL2;
  uint8_t statusPlacaL3;
}STATUS_GST;

STATUS_GST *getPtrStatusGst(void);

void masterControlInit();
void masterControlTask();
void sendRefreshCommand();
void processStatusCommand();
void masterControlHandlePacket(uint8_t* packet, uint8_t size);

#endif