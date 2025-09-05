#include <Arduino.h>
#include <lvgl.h>
#include "events.h"

static char inputBuffer[16]; // Buffer para armazenar o número digitado 
static int bufferIndex = 0; // Índice do próximo caractere no buffer 
static bool isInputMode = false; // Estado para indicar se estamos digitando
static bool tecladoHabilitado = false; 
static lv_obj_t *active_mbox = NULL; 
static lv_timer_t *mbox_timer = NULL;

//*****************************************************************************
// evento inicializacao da tela
//*****************************************************************************
void ui_telaMain_event_handler (lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);

    switch (code) {
        case LV_EVENT_SCREEN_LOADED:
            Serial.println("LV_EVENT_SCREEN_LOADED");
            break;
        default:

            break;
    }
}
//*****************************************************************************
// Botão ON/OFF 
//*****************************************************************************
/* static void ui_telaMain_btn_onoff_event_handler (lv_event_t *e){
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *id_btn = lv_event_get_target(e);
  lv_ui *ui = getUiTelaMain();
  STATUS_GST *gst = getPtrStatusGst();
  char convstr[32];

  if (code == LV_EVENT_CLICKED) {
    if (id_btn == ui->ui_telaMain_btnOnOff) {
      Serial.println("Clique ON/OFF");
      //Verifica o status do botao de ON/OFF.
      if(gst->statusOnOff==0){
        gst->statusOnOff = 1;
        lv_obj_set_style_bg_color(ui->ui_telaMain_btnOnOff, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_label_set_text(ui->ui_telaMain_label_btnOnOff, "LIGAR");
      }else{
        gst->statusOnOff = 0;
        lv_obj_set_style_bg_color(ui->ui_telaMain_btnOnOff, lv_color_hex(0xFF002D), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_label_set_text(ui->ui_telaMain_label_btnOnOff, "DESLIGAR");
      }
    }
  }
} */
//*****************************************************************************
// Seleção de container de fases e cbHab
//*****************************************************************************
//responsável pela seleção das fases e pelas caixas de seleção que habilitam/desabilitam as fases
static void ui_telaMain_container_fase_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_ui *ui = getUiTelaMain();
    STATUS_GST *gst = getPtrStatusGst();

    // Lógica para os containers de fase (utiliza LV_EVENT_CLICKED)
    if (code == LV_EVENT_CLICKED) {
        if (gst->atvGrupoFases == 0) { // Se as fases não estiverem agrupadas, seleciona a fase clicada
            if (target == ui->ui_telaMain_cont_L1) {
                ativarL1(ui, gst);
            } else if (target == ui->ui_telaMain_cont_L2) {
                ativarL2(ui, gst);
            } else if (target == ui->ui_telaMain_cont_L3) {
                ativarL3(ui, gst);
            bloquearTeclado(ui, gst); //função de bloquear o teclado
            }
        }      
        // Lógica para os checkboxes 
          if (target == ui->ui_telaMain_cbHabL1) {
          Serial.println("Clique cb habL1");
          gst->habL1 = !gst->habL1; // Alterna o valor (toggle)
        } else if (target == ui->ui_telaMain_cbHabL2) {
          Serial.println("Clique cb habL2");
          gst->habL2 = !gst->habL2;
        } else if (target == ui->ui_telaMain_cbHabL3) {
          Serial.println("Clique cb habL3");
          gst->habL3 = !gst->habL3;
        }
        altModecbHab(ui, gst);
    }
}
//*****************************************************************************
// botões de incremento e decremento (UP/DOWN)
//*****************************************************************************
//Responsável pelos eventos dos botões que incrementam/decrementam o valor dos setPoints
static void ui_telaMain_btn_updown_event_handler (lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *id_btn = lv_event_get_target(e);
    lv_ui *ui = getUiTelaMain();
    STATUS_GST *gst = getPtrStatusGst();
    char convstr[32];
    
//Botões de incremento
    if (code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
        if (id_btn == ui->ui_telaMain_btn_upL1) { //Controle do botão UP da Fase 1
          Serial.println("clique UP L1");
          ativarL1(ui, gst);                    //Ativa a fase referente ao botão apertado
          incPercent(PERCENT_FASE_L1, gst);
          // atualiza na tela
          showSetPointL1(ui, gst);
          Serial.println(gst->setPointPercentL1);

        } else if (id_btn == ui->ui_telaMain_btn_upL2) {//Controle do botão UP da Fase 2
            Serial.println("clique UP L2");
            if(gst->atvGrupoFases == 1){               //Controle caso agrupado true
              incPercent(PERCENT_ALL, gst);                            
            }else if(gst->atvGrupoFases == 0){          //Controle caso agrupado false (somente L2)
              ativarL2(ui, gst);                        //Ativa a fase referente ao botão apertado
              incPercent(PERCENT_FASE_L2, gst);
            }
            // Atualiza na tela
            showSetPointsPercents(ui, gst);

          }else if (id_btn == ui->ui_telaMain_btn_upL3) {//Controle do botão UP da Fase 3
            Serial.println("clique UP L3");
            ativarL3(ui, gst);                           //Ativa a fase referente ao botão apertado
            incPercent(PERCENT_FASE_L3, gst);
            // atualiza na tela
            showSetPointL3(ui, gst);                     //Atualiza o valor da label de setPoint da fase 3 
            Serial.println(gst->setPointPercentL3);

//Botões de decremento
        }else if (id_btn == ui->ui_telaMain_btn_downL1) {//Controle do botão DOWN da Fase 1
          Serial.println("clique DOWN L1");
          ativarL1(ui, gst);
          decPercent(PERCENT_FASE_L1, gst);
          // atualiza na tela
          showSetPointL1(ui, gst);
          Serial.println(gst->setPointPercentL1);

        }else if (id_btn == ui->ui_telaMain_btn_downL2){//Controle do botão DOWN da Fase 2
          Serial.println("clique DOWN L2");
          if(gst->atvGrupoFases == 1){                  //Controle caso agrupado true
            decPercent(PERCENT_ALL, gst);
          }else if(gst->atvGrupoFases == 0){            //Controle caso agrupado false (Somente L2)
            ativarL2(ui, gst);
            decPercent(PERCENT_FASE_L2, gst);
          }
          // Atualiza na tela
          showSetPointsPercents(ui, gst);

        }else if (id_btn == ui->ui_telaMain_btn_downL3) {//Controle do botão DOWN da Fase 3
          Serial.println("clique DOWN L3");
          ativarL3(ui, gst);
          decPercent(PERCENT_FASE_L3, gst);
          // atualiza na tela
          showSetPointL3(ui, gst);
          Serial.println(gst->setPointPercentL3);
        }
        bloquearTeclado(ui, gst); 
    }   
}

//*****************************************************************************
// botoes de set de frequencia e slider
//*****************************************************************************

static void ui_telaMain_container_frequency_event_handler (lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *id_btn = lv_event_get_target(e);
    lv_ui *ui = getUiTelaMain();
    STATUS_GST *gst = getPtrStatusGst();
    char convstr[32];

    if (code == LV_EVENT_CLICKED) {
        if (id_btn == ui->ui_telaMain_btnFreq50) {
            Serial.println("clique FREQ 50");
            gst->freqAt = 50.0;
            sprintf(convstr,"•\n%.1fHz", gst->freqAt); //Pega frequência atual e converte em string
            lv_label_set_text(ui->ui_telaMain_label_freqAtual, convstr);
            lv_slider_set_range(ui->ui_telaMain_sliderFreq, SET_POINT_FREQ50_MIN, SET_POINT_FREQ50_MAX);//Altera o range do slider
            lv_slider_set_value(ui->ui_telaMain_sliderFreq, SET_POINT_FREQCENT50, LV_ANIM_OFF);
        }
        else if (id_btn == ui->ui_telaMain_btnFreq60) {
            Serial.println("clique FREQ 60");
            gst->freqAt = 60.0;
            sprintf(convstr,"•\n%.1fHz", gst->freqAt); //Pega frequência atual e converte em string
            lv_label_set_text(ui->ui_telaMain_label_freqAtual, convstr);
            lv_slider_set_range(ui->ui_telaMain_sliderFreq, SET_POINT_FREQ60_MIN, SET_POINT_FREQ60_MAX); //Altera o range do slider
            lv_slider_set_value(ui->ui_telaMain_sliderFreq, SET_POINT_FREQCENT60, LV_ANIM_OFF);
        }
    }
    //Faz o slider mudar o valor da frequencia e alterar a label
    if (code == LV_EVENT_VALUE_CHANGED){             
      if (id_btn == ui->ui_telaMain_sliderFreq){
        gst-> freqAt = lv_slider_get_value(id_btn);
        gst-> freqAt /= 10;
        sprintf(convstr,"•\n%.1fHz", gst->freqAt);
        Serial.println("Clique slider");
        lv_label_set_text(ui->ui_telaMain_label_freqAtual, convstr);
      }
    }
}

//*****************************************************************************
// Controle de incremento/decremento (Seleção de passo)
//*****************************************************************************
//Responsável pelas checkbox de seleção de passo 
static void ui_telaMain_container_passo_event_handler (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *id_btn = lv_event_get_target(e);
    lv_ui *ui = getUiTelaMain();
    STATUS_GST *gst = getPtrStatusGst();

  if (code == LV_STATE_CHECKED) {                                         //Quando a checkbox for marcada, ela é desabilitada e limpa o estado das outras
    if (id_btn == ui->ui_telaMain_selPasso1) {
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                        //Desabilita a checkbox 1 
      lv_obj_clear_state(ui->ui_telaMain_selPasso2, LV_STATE_CHECKED);  //limpa o status da checkbox 2 
      lv_obj_clear_state(ui->ui_telaMain_selPasso2, LV_STATE_DISABLED); //Habilita a checkbox 2 
      lv_obj_clear_state(ui->ui_telaMain_selPasso3, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso3, LV_STATE_DISABLED);  
      lv_obj_clear_state(ui->ui_telaMain_selPasso4, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso4, LV_STATE_DISABLED);
      Serial.println("CB1 Clicked");
      gst-> valPasso = 5;                                                 //Altera o valor de passo para 0.5                                             
    } else if (id_btn == ui->ui_telaMain_selPasso2) {
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso1, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso1, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso3, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso3, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso4, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso4, LV_STATE_DISABLED);
      Serial.println("CB2 Clicked");
      gst-> valPasso = 10;                                                 //Altera o valor de passo para 1
    } else if (id_btn == ui->ui_telaMain_selPasso3) {
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso1, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso1, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso2, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso2, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso4, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso4, LV_STATE_DISABLED);
      Serial.println("CB3 Clicked");
      gst-> valPasso = 50;                                                 //Altera o valor de passo para 5
    } else if (id_btn == ui->ui_telaMain_selPasso4) {
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso1, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso1, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso2, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso2, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso3, LV_STATE_CHECKED);
      lv_obj_clear_state(ui->ui_telaMain_selPasso3, LV_STATE_DISABLED);
      Serial.println("CB4 Clicked");
      gst-> valPasso = 100;                                                //Altera o valor de passo para 10
    }
  }
}

//*****************************************************************************
// selecao de modo (% ou V)
//*****************************************************************************
//Responsável pelas checkbox de seleção modo 

static void ui_telaMain_container_mode_event_handler (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *id_btn = lv_event_get_target(e);
    lv_ui *ui = getUiTelaMain();
    STATUS_GST *gst = getPtrStatusGst();

    if(code == LV_STATE_CHECKED){                                              //Quando a checkbox for marcada fica bloqueada e limpa o estado da outra
    if (id_btn == ui->ui_telaMain_selModeGrandeza){
      Serial.println("Clique tensão");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                             //Desabilita a checkbox
      lv_obj_clear_state(ui->ui_telaMain_selModePercent, LV_STATE_CHECKED);  //limpa o status da checkbox porcentagem
      lv_obj_clear_state(ui->ui_telaMain_selModePercent, LV_STATE_DISABLED); //Habilita a checkbox porcentagem
      gst->modeVolt = STATUS_TENSAO;
      Serial.println(gst->modeVolt);
    }else if(id_btn == ui->ui_telaMain_selModePercent){
      Serial.println("Clique Percent");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);
      lv_obj_clear_state(ui->ui_telaMain_selModeGrandeza, LV_STATE_CHECKED); //limpa o status da checkbox grandeza
      lv_obj_clear_state(ui->ui_telaMain_selModeGrandeza, LV_STATE_DISABLED);//Habilita a checkbox grandeza
      gst->modeVolt = STATUS_PERCENT;
      Serial.println(gst->modeVolt);
    }
  }
}

//*****************************************************************************
// botões agrupar, nominal e config
//*****************************************************************************
static void ui_telaMain_container_modegrupo_event_handler (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *id_btn = lv_event_get_target(e);
  lv_ui *ui = getUiTelaMain();
  STATUS_GST *gst = getPtrStatusGst();
  char convstr[32];
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Botão agrupar: Agrupa/Desagrupa as fases
  if (code == LV_EVENT_CLICKED) {                   
    if (id_btn == ui->ui_telaMain_btnAgrupar) {        //verifica se o botao apertado foi o de agrupar/desagrupar
      Serial.println("clique botao agrupar");
      // agrupar agora?
      alternarGrupoFases(ui, gst);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Botão nominal: Seta o valor das tres fases para 100% e atualiza as labels de setPoint
    } else if(id_btn == ui->ui_telaMain_btnNominal){                        //Clique do botão nominal
        Serial.println("Clique botão nominal");
        // define os setpoints para o valor selecionado na escala 
        gst->setPointPercentL1 = VAL_100PCT;
        gst->setPointPercentL2 = VAL_100PCT;
        gst->setPointPercentL3 = VAL_100PCT;                                
        // atualiza na tela
        showSetPointsPercents(ui, gst);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Botão config
    } else if(id_btn == ui->ui_telaMain_btnConfig){                   //Clique do botão config 
        Serial.println("Clique botao config");
        Serial.println("Fator de potencia: " + String(gst->fatorDePotenciaL1));
        Serial.println("Corrente: " + String(gst->correnteL1));
    }
    bloquearTeclado(ui, gst); //Se qualquer um dos tres botoes for apertado, bloqueia o teclado caso o mesmo esteja ativo 
  }
}

//*****************************************************************************
// botões porcentagem da escala
//*****************************************************************************
static void ui_telaMain_btn_percent_event_handler (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *id_btn = lv_event_get_target(e);
  lv_ui *ui = getUiTelaMain();
  STATUS_GST *gst = getPtrStatusGst();
  char convstr[32];

  if (code == LV_EVENT_CLICKED){
    if(id_btn == ui->ui_telaMain_btnPercent1){               //Se o botao de porcentagem 1 (40%) for apertado
      Serial.println("Clique 40%");
      setPercent(VAL_40PCT, gst);
    } else if (id_btn == ui->ui_telaMain_btnPercent2){       //Se o botao de porcentagem 2 (60%) for apertado
        Serial.println("Clique 60%");
        setPercent(VAL_60PCT, gst);
    } else if (id_btn == ui->ui_telaMain_btnPercent3){       //Se o botao de porcentagem 3 (80%) for apertado
        Serial.println("Clique 80%");
        setPercent(VAL_80PCT, gst);
    } else if (id_btn == ui->ui_telaMain_btnPercent4){       //Se o botao de porcentagem 4 (100%) for apertado
        Serial.println("Clique 100%");
        setPercent(VAL_100PCT, gst);
    } else if (id_btn == ui->ui_telaMain_btnPercent5){       //Se o botao de porcentagem 5 (120%) for apertado
        Serial.println("Clique 120%");
        setPercent(VAL_120PCT, gst);
      }
      //Atualiza na tela
      bloquearTeclado(ui, gst);
      showSetPointsPercents(ui, gst);  
  } 
}

//*****************************************************************************
// botões seleção de escala
//*****************************************************************************
static void ui_telaMain_container_scale_event_handler (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *id_btn = lv_event_get_target(e);
  lv_ui *ui = getUiTelaMain();
  STATUS_GST *gst = getPtrStatusGst();
  char convstr[32];

  if (code == LV_EVENT_CLICKED) {
    if (id_btn == ui->ui_telaMain_selEscala0){                           //Seleção botão 0 (12Vac)
      Serial.println("Clique btn esc 0 (12Vac)");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                          //Desabilita a checkbox 0
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_CHECKED);  //limpa o status da checkbox 1 
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_DISABLED); //Habilita a checkbox 1 
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_CHECKED);  //limpa o status da checkbox 2 
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_DISABLED); //Habilita a checkbox 2
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_CHECKED);  //limpa o status da checkbox 3
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_DISABLED); //Habilita a checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_CHECKED);  //limpa o status da checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_DISABLED); //Habilita a checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_CHECKED);  //limpa o status da checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_DISABLED); //Habilita a checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_CHECKED);  //limpa o status da checkbox 6 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_DISABLED); //Habilita a checkbox 6
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_CHECKED);  //limpa o status da checkbox 7 
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_DISABLED); //Habilita a checkbox 7
      gst->vEscala = VAL_CHECKBOX_ESCALA0;                                  //Seta a variável de seleção de escala para 12Vac
      gst->modeAcDc = 0;
      Serial.println("valor atual da escala: " + String(gst->vEscala));
      showSetPointsPercents(ui, gst);
      

    }else if(id_btn == ui->ui_telaMain_selEscala1) {                     //Seleção botão 1 (24Vac)
      Serial.println("Clique btn esc 1 (24Vac)");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                          //Desabilita a checkbox 1
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_CHECKED);  //limpa o status da checkbox 0 
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_DISABLED); //Habilita a checkbox 0  
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_CHECKED);  //limpa o status da checkbox 2 
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_DISABLED); //Habilita a checkbox 2
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_CHECKED);  //limpa o status da checkbox 3
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_DISABLED); //Habilita a checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_CHECKED);  //limpa o status da checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_DISABLED); //Habilita a checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_CHECKED);  //limpa o status da checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_DISABLED); //Habilita a checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_CHECKED);  //limpa o status da checkbox 6 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_DISABLED); //Habilita a checkbox 6
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_CHECKED);  //limpa o status da checkbox 7 
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_DISABLED); //Habilita a checkbox 7
      gst->vEscala = VAL_CHECKBOX_ESCALA1;                                  //Seta a variável de seleção de escala para 24Vac
      gst->modeAcDc = 0;
      Serial.println("valor atual da escala: " + String(gst->vEscala));
      showSetPointsPercents(ui, gst);
      
    } else if (id_btn == ui->ui_telaMain_selEscala2){  //Seleção botão 2 (110Vac)
      Serial.println("Clique btn esc 2 (110Vac)");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                          //Desabilita a checkbox 2
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_CHECKED);  //limpa o status da checkbox 0 
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_DISABLED); //Habilita a checkbox 0 
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_CHECKED);  //limpa o status da checkbox 1 
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_DISABLED); //Habilita a checkbox 1
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_CHECKED);  //limpa o status da checkbox 3
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_DISABLED); //Habilita a checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_CHECKED);  //limpa o status da checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_DISABLED); //Habilita a checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_CHECKED);  //limpa o status da checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_DISABLED); //Habilita a checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_CHECKED);  //limpa o status da checkbox 6 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_DISABLED); //Habilita a checkbox 6
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_CHECKED);  //limpa o status da checkbox 7 
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_DISABLED); //Habilita a checkbox 7 
      gst->vEscala = VAL_CHECKBOX_ESCALA2;                                  //Seta a variável de seleção de escala para 110Vac
      gst->modeAcDc = 0;
      showSetPointsPercents(ui, gst);

    } else if (id_btn == ui->ui_telaMain_selEscala3){  //Seleção botão 3 (220Vac)
      Serial.println("Clique btn esc 3 (220Vac)");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                          //Desabilita a checkbox 3
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_CHECKED);  //limpa o status da checkbox 0 
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_DISABLED); //Habilita a checkbox 0  
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_CHECKED);  //limpa o status da checkbox 1 
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_DISABLED); //Habilita a checkbox 1
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_CHECKED);  //limpa o status da checkbox 2
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_DISABLED); //Habilita a checkbox 2 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_CHECKED);  //limpa o status da checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_DISABLED); //Habilita a checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_CHECKED);  //limpa o status da checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_DISABLED); //Habilita a checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_CHECKED);  //limpa o status da checkbox 6 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_DISABLED); //Habilita a checkbox 6
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_CHECKED);  //limpa o status da checkbox 7 
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_DISABLED); //Habilita a checkbox 7
      gst->vEscala = VAL_CHECKBOX_ESCALA3;                                  //Seta a variável de seleção de escala para 220Vac
      gst->modeAcDc = 0;
      Serial.println("valor atual da escala: " + String(gst->vEscala));
      showSetPointsPercents(ui, gst);
      

    } else if (id_btn == ui->ui_telaMain_selEscala4){  //Seleção botão 4 (380Vac)
      Serial.println("Clique btn esc 4 (380Vac)");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                          //Desabilita a checkbox 4
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_CHECKED);  //limpa o status da checkbox 0 
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_DISABLED); //Habilita a checkbox 0  
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_CHECKED);  //limpa o status da checkbox 1 
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_DISABLED); //Habilita a checkbox 1
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_CHECKED);  //limpa o status da checkbox 2
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_DISABLED); //Habilita a checkbox 2 
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_CHECKED);  //limpa o status da checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_DISABLED); //Habilita a checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_CHECKED);  //limpa o status da checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_DISABLED); //Habilita a checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_CHECKED);  //limpa o status da checkbox 6 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_DISABLED); //Habilita a checkbox 6
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_CHECKED);  //limpa o status da checkbox 7 
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_DISABLED); //Habilita a checkbox 7  
      gst->vEscala = VAL_CHECKBOX_ESCALA4;                                  //Seta a variável de seleção de escala para 380Vac
      gst->modeAcDc = 0;
      Serial.println("valor atual da escala: " + String(gst->vEscala));
      showSetPointsPercents(ui, gst);
      
    } else if (id_btn == ui->ui_telaMain_selEscala5){  //Seleção botão 5 (440Vac)
      Serial.println("Clique btn esc 5 (440Vac)");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                          //Desabilita a checkbox 5
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_CHECKED);  //limpa o status da checkbox 0 
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_DISABLED); //Habilita a checkbox 0  
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_CHECKED);  //limpa o status da checkbox 1 
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_DISABLED); //Habilita a checkbox 1
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_CHECKED);  //limpa o status da checkbox 2
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_DISABLED); //Habilita a checkbox 2 
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_CHECKED);  //limpa o status da checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_DISABLED); //Habilita a checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_CHECKED);  //limpa o status da checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_DISABLED); //Habilita a checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_CHECKED);  //limpa o status da checkbox 6 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_DISABLED); //Habilita a checkbox 6
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_CHECKED);  //limpa o status da checkbox 7 
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_DISABLED); //Habilita a checkbox 7
      gst->vEscala = VAL_CHECKBOX_ESCALA5;                                  //Seta a variável de seleção de escala para 440Vac
      gst->modeAcDc = 0;
      Serial.println("valor atual da escala: " + String(gst->vEscala));
      showSetPointsPercents(ui, gst);
   
 
    } else if (id_btn == ui->ui_telaMain_selEscala6){  //Seleção botão 6 (480Vac)
      Serial.println("Clique btn esc 6 (480Vac)");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                          //Desabilita a checkbox 6
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_CHECKED);  //limpa o status da checkbox 0 
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_DISABLED); //Habilita a checkbox 0  
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_CHECKED);  //limpa o status da checkbox 1 
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_DISABLED); //Habilita a checkbox 1
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_CHECKED);  //limpa o status da checkbox 2
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_DISABLED); //Habilita a checkbox 2 
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_CHECKED);  //limpa o status da checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_DISABLED); //Habilita a checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_CHECKED);  //limpa o status da checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_DISABLED); //Habilita a checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_CHECKED);  //limpa o status da checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_DISABLED); //Habilita a checkbox 5
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_CHECKED);  //limpa o status da checkbox 7 
      lv_obj_clear_state(ui->ui_telaMain_selEscala7, LV_STATE_DISABLED); //Habilita a checkbox 7  
      gst->vEscala = VAL_CHECKBOX_ESCALA6;                                  //Seta a variável de seleção de escala para 480Vac
      gst->modeAcDc = 0;
      Serial.println("valor atual da escala: " + String(gst->vEscala));
      showSetPointsPercents(ui, gst);
      

    } else if (id_btn == ui->ui_telaMain_selEscala7){  //Seleção botão 7 (64Vdc)
      Serial.println("Clique btn esc 7 (64Vdc)");
      lv_obj_add_state(id_btn, LV_STATE_DISABLED);                          //Desabilita a checkbox 7
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_CHECKED);  //limpa o status da checkbox 0 
      lv_obj_clear_state(ui->ui_telaMain_selEscala0, LV_STATE_DISABLED); //Habilita a checkbox 0  
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_CHECKED);  //limpa o status da checkbox 1 
      lv_obj_clear_state(ui->ui_telaMain_selEscala1, LV_STATE_DISABLED); //Habilita a checkbox 1
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_CHECKED);  //limpa o status da checkbox 2
      lv_obj_clear_state(ui->ui_telaMain_selEscala2, LV_STATE_DISABLED); //Habilita a checkbox 2 
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_CHECKED);  //limpa o status da checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala3, LV_STATE_DISABLED); //Habilita a checkbox 3 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_CHECKED);  //limpa o status da checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala4, LV_STATE_DISABLED); //Habilita a checkbox 4 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_CHECKED);  //limpa o status da checkbox 5 
      lv_obj_clear_state(ui->ui_telaMain_selEscala5, LV_STATE_DISABLED); //Habilita a checkbox 5
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_CHECKED);  //limpa o status da checkbox 6 
      lv_obj_clear_state(ui->ui_telaMain_selEscala6, LV_STATE_DISABLED); //Habilita a checkbox 6 
      gst->vEscala = VAL_CHECKBOX_ESCALA7;                                  //Seta a variável de seleção de escala para 64Vdc
      gst->modeAcDc = 1; 
      Serial.println("valor atual da escala: " + String(gst->vEscala));
      showSetPointsPercents(ui, gst);
    }
    bloquearTeclado(ui, gst);
  }
}

//*****************************************************************************
// Botoes de sequencia de fases L1,L2,L3
//*****************************************************************************
static void ui_telaMain_btn_seq_fase_event_handler (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *id_btn = lv_event_get_target(e);
  lv_ui *ui = getUiTelaMain();
  STATUS_GST *gst = getPtrStatusGst();

  if(code == LV_EVENT_CLICKED){
    if(id_btn == ui->ui_telaMain_btnSeqL1L2){                                                                       //inverte as fases L1 e L2
      Serial.println("Clique inverte L1/L2");    
      lv_label_set_text(ui->ui_telaMain_label_seq_l1, "L2");                                                        //Altera as labels de sequencia de fase
      lv_label_set_text(ui->ui_telaMain_label_seq_l2, "L1");
      lv_label_set_text(ui->ui_telaMain_label_seq_l3, "L3");
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L1, lv_color_hex(0x922034), LV_PART_MAIN|LV_STATE_DEFAULT);    //Destaca as fases invertidas em vermelho
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L2, lv_color_hex(0x922034), LV_PART_MAIN|LV_STATE_DEFAULT);  
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L3, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_sequencia, lv_color_hex(0x922034), LV_PART_MAIN|LV_STATE_DEFAULT);
      gst-> outL1 = CONST_FASE_L2;
      gst-> outL2 = CONST_FASE_L1;
      gst-> outL3 = CONST_FASE_L3;
    }else if(id_btn == ui->ui_telaMain_btnSeqL2L3){                                                                       //inverte as fases L2 e L3
      Serial.println("Clique inverte L2/L3");
      lv_label_set_text(ui->ui_telaMain_label_seq_l1, "L1");
      lv_label_set_text(ui->ui_telaMain_label_seq_l2, "L3");
      lv_label_set_text(ui->ui_telaMain_label_seq_l3, "L2");
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L1, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L2, lv_color_hex(0x922034), LV_PART_MAIN|LV_STATE_DEFAULT);  
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L3, lv_color_hex(0x922034), LV_PART_MAIN|LV_STATE_DEFAULT);
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_sequencia, lv_color_hex(0x922034), LV_PART_MAIN|LV_STATE_DEFAULT);
      gst-> outL1 = CONST_FASE_L1;
      gst-> outL2 = CONST_FASE_L3;
      gst-> outL3 = CONST_FASE_L2;  
    }else if(id_btn == ui->ui_telaMain_btnSeqL1L3){                                                                       //inverte as fases L1 e L3
      Serial.println("Clique inverte L1/L3");
      lv_label_set_text(ui->ui_telaMain_label_seq_l1, "L3");
      lv_label_set_text(ui->ui_telaMain_label_seq_l2, "L2");
      lv_label_set_text(ui->ui_telaMain_label_seq_l3, "L1");
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L1, lv_color_hex(0x922034), LV_PART_MAIN|LV_STATE_DEFAULT);
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L2, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);  
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L3, lv_color_hex(0x922034), LV_PART_MAIN|LV_STATE_DEFAULT);
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_sequencia, lv_color_hex(0x922034), LV_PART_MAIN|LV_STATE_DEFAULT);
      gst-> outL1 = CONST_FASE_L3;
      gst-> outL2 = CONST_FASE_L2;
      gst-> outL3 = CONST_FASE_L1;
    }else if(id_btn == ui->ui_telaMain_btnSeqL1L2L3){                                                                       //ordena as fases novamente
      Serial.println("Clique organiza as fases L1/L2/L3");
      lv_label_set_text(ui->ui_telaMain_label_seq_l1, "L1");
      lv_label_set_text(ui->ui_telaMain_label_seq_l2, "L2");
      lv_label_set_text(ui->ui_telaMain_label_seq_l3, "L3");
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L1, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);            //retira o destaque das fases invertidas 
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L2, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);  
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L3, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);
      lv_obj_set_style_bg_color(ui->ui_telaMain_cont_sequencia, lv_color_hex(0x414242), LV_PART_MAIN|LV_STATE_DEFAULT);
      gst-> outL1 = CONST_FASE_L1;
      gst-> outL2 = CONST_FASE_L2;
      gst-> outL3 = CONST_FASE_L3;
    }
  }
}

//*****************************************************************************
// Botoes do teclado
//*****************************************************************************
static void ui_telaMain_btn_teclado_event_handler(lv_event_t *e) { 
  lv_event_code_t code = lv_event_get_code(e); 
  lv_obj_t *id_btn = lv_event_get_target(e); 
  lv_ui *ui = getUiTelaMain(); 
  STATUS_GST *gst = getPtrStatusGst();
  
  
  if (code == LV_EVENT_CLICKED) { 
    if (id_btn == ui->ui_telaMain_btn_ok) { // Quando "OK" é pressionado
      Serial.println("Clique btn ok"); 
      if (isInputMode) { 
        if (bufferIndex != 0){ 
          inputBuffer[bufferIndex] = '\0'; // Finaliza a string corretamente 
          double inputValue = atof(inputBuffer); // Converte para número 
          
          // Garante que o valor digitado está entre 0% e 127% 
          if (inputValue > 127.0) {
            // Cria a message box exibindo a mensagem "Valor invalido" 
            active_mbox = lv_msgbox_create(lv_scr_act(), "Aviso", "Valor invalido", NULL, true);
            lv_obj_center(active_mbox);
            // Adiciona callback para detectar quando a message box for fechada manualmente
            lv_obj_add_event_cb(active_mbox, mbox_close_event_cb, LV_EVENT_DELETE, NULL);
            
            bloquearTeclado(ui, gst);
            showSetPointsPercents(ui, gst);

            // Cria um timer que fechará a message box após 2,5 segundos (2500 ms)
            mbox_timer = lv_timer_create([](lv_timer_t *timer) {
                if (lv_obj_is_valid(active_mbox)) { // Se a message box ainda estiver ativa, deleta-a
                    lv_obj_del(active_mbox);
                    active_mbox = NULL;
                }
                mbox_timer = NULL;   // Reseta o ponteiro do timer
            }, 2500, NULL);

            return; // Aborta o processamento e sai do handler
          }
          
          char formattedValue[20]; 
          snprintf(formattedValue, sizeof(formattedValue), "%.1f%%", inputValue); 
          Serial.print("Valor fixado: "); 
          Serial.println(formattedValue); // Mostra a porcentagem atual selecionada 
          //verifica a fase ativa e atribui o valor do input à(s) respectiva(s) variáveis de setPoint
          if (gst->atvL1) { 
            gst->setPointPercentL1 = inputValue;  
            showSetPointL1(ui, gst); 
          } 
          if (gst->atvL2) { 
            gst->setPointPercentL2 = inputValue;  
            showSetPointL2(ui, gst); 
          } 
          if (gst->atvL3) { 
            gst->setPointPercentL3 = inputValue;  
            showSetPointL3(ui, gst); 
          } 
          if (gst->atvGrupoFases) { 
            gst->setPointPercentL1 = gst->setPointPercentL2 = gst->setPointPercentL3 = inputValue; 
            showSetPointsPercents(ui, gst); 
          } 
        }
        //bloqueia o teclado após a inserção dos valores nas labels
        bloquearTeclado(ui,gst);
      } 
      else {  //se fora do input mode, desbloqueia o teclado e salva os valores atuais das fases em variaveis de memória 
        desbloquearTeclado(ui, gst);
      } 
    } else if (id_btn == ui->ui_telaMain_btn_cancel) { // Quando "Cancel" é pressionado limpa o valor digitado, se apertado quando buffer limpo, bloquear teclado
      Serial.println("Clique btn cancel"); 
      if (isInputMode) {  //Se o inputMode está ativo
        if (bufferIndex == 0){  // se o usuário nao digitou nada e apertou cancel, bloqueia o teclado
          bloquearTeclado(ui,gst);
        } 
        else{ //limpa o buffer e atualizao as labels com o valor restaurado da váriavel de memória
          Serial.println("Entrada cancelada."); 
          bufferIndex = 0; 
          memset(inputBuffer, 0, sizeof(inputBuffer)); 
          restoreSetPointsPercents(ui, gst); 
          if (gst->atvL1) showSetPointL1(ui, gst);
          else if (gst->atvL2) showSetPointL2(ui, gst); 
          else if (gst->atvL3) showSetPointL3(ui, gst); 
          else if (gst->atvGrupoFases) showSetPointsPercents(ui, gst);
        }           
      } 
    } else if (isInputMode) { // Captura números do teclado apenas se o modo de entrada estiver ativo 
      if (bufferIndex < 3) { // Limita a entrada a no máximo 3 caracteres
        const char *btnText = lv_label_get_text(lv_obj_get_child(id_btn, 0)); 
        if (btnText && btnText[0] >= '0' && btnText[0] <= '9') { // Garante que é um número válido 
          inputBuffer[bufferIndex++] = btnText[0]; 
          inputBuffer[bufferIndex] = '\0'; // Finaliza corretamente a string 
          Serial.print("Digitando: "); 
          Serial.println(inputBuffer); 
          
          char formattedValue[20]; 
          snprintf(formattedValue, sizeof(formattedValue), "%s%%", inputBuffer); // Atualiza a label da fase ativa com "%"
          if (gst->atvL1) lv_label_set_text(ui->ui_telaMain_lbSetL1, formattedValue); 
          if (gst->atvL2) lv_label_set_text(ui->ui_telaMain_lbSetL2, formattedValue); 
          if (gst->atvL3) lv_label_set_text(ui->ui_telaMain_lbSetL3, formattedValue); 
          if (gst->atvGrupoFases) { 
            lv_label_set_text(ui->ui_telaMain_lbSetL1, formattedValue); 
            lv_label_set_text(ui->ui_telaMain_lbSetL2, formattedValue); 
            lv_label_set_text(ui->ui_telaMain_lbSetL3, formattedValue); 
          } 
        } 
      } else { 
        Serial.println("Limite máximo de 3 dígitos atingido."); // Mensagem opcional para depuração
      } 
    } 
  } 
}

//*****************************************************************************
// Funções auxiliares
//*****************************************************************************
//Atualiza o valor das variáveis para tornar apenas a fase 1 ativa
void ativarL1(lv_ui *ui, STATUS_GST *gst) {                                                     
  Serial.println("Clique fase 1");
  gst->atvL1 = 1;
  gst->atvL2 = 0;
  gst->atvL3 = 0;
  //esconde a borda de duas fases, mostra a borda da fase ativa
  lv_obj_set_style_border_width(ui->ui_telaMain_cont_L1, 5, LV_PART_MAIN | LV_STATE_DEFAULT); 
  lv_obj_set_style_border_width(ui->ui_telaMain_cont_L2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui->ui_telaMain_cont_L3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Atualiza o valor das variáveis para tornar apenas a fase 2 ativa
void ativarL2(lv_ui *ui, STATUS_GST *gst) {
  Serial.println("Clique fase 2");
  gst->atvL1 = 0;
  gst->atvL2 = 1;
  gst->atvL3 = 0;
  //esconde a borda de duas fases, mostra a borda da fase ativa
  lv_obj_set_style_border_width(ui->ui_telaMain_cont_L1, 0, LV_PART_MAIN | LV_STATE_DEFAULT); 
  lv_obj_set_style_border_width(ui->ui_telaMain_cont_L2, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui->ui_telaMain_cont_L3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Atualiza o valor das variáveis para tornar apenas a fase 3 ativa
void ativarL3(lv_ui *ui, STATUS_GST *gst) {                                                     
  Serial.println("Clique fase 3");                                                               
  gst->atvL1 = 0;
  gst->atvL2 = 0;
  gst->atvL3 = 1;
  //esconde a borda de duas fases, mostra a borda da fase ativa
  lv_obj_set_style_border_width(ui->ui_telaMain_cont_L1, 0, LV_PART_MAIN | LV_STATE_DEFAULT); 
  lv_obj_set_style_border_width(ui->ui_telaMain_cont_L2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui->ui_telaMain_cont_L3, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Faz a conversão de porcentagem para tensao com base na escala selecionada, atribui o valor à variavel de tensao e atualiza as labels de porcentagem e tensao 
void showSetPointL1(lv_ui *ui, STATUS_GST *gst) {
    char convstr[32];
    // Exibe o valor atual de porcentagem diretamente
    if (gst->setPointPercentL1 > SET_POINT_PERCENT_MAX) gst->setPointPercentL1 = SET_POINT_PERCENT_MAX; // Limita ao máximo
    if (gst->setPointPercentL1 < 0.0f) gst->setPointPercentL1 = 0.0f; // Limita ao mínimo de 0%
    // Atualiza a label da porcentagem na interface
    sprintf(convstr, "%.1f%%", gst->setPointPercentL1); // Converte o valor percentual em string com %
    lv_label_set_text(ui->ui_telaMain_lbSetL1, convstr); // Atualiza a label de porcentagem
    // Converte o valor percentual para tensão correspondente e exibe
    gst->setPointL1 = (gst->setPointPercentL1 * gst->vEscala) / 1000.0; // Calcula a tensão com base na porcentagem
    sprintf(convstr, "%.1f", gst->setPointL1); // Converte o valor de tensão em string
    //lv_label_set_text(ui->ui_telaMain_lbDisplayL1, convstr); // Atualiza a label de tensão
}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //Faz a conversão de porcentagem para tensao com base na escala selecionada, atribui o valor à variavel de tensao e atualiza as labels de porcentagem e tensao
 void showSetPointL2(lv_ui *ui, STATUS_GST *gst) {
    char convstr[32];
    // Exibe o valor atual de porcentagem diretamente
    if (gst->setPointPercentL2 > SET_POINT_PERCENT_MAX) gst->setPointPercentL2 = SET_POINT_PERCENT_MAX; // Limita ao máximo
    if (gst->setPointPercentL2 < 0.0f) gst->setPointPercentL2 = 0.0f; // Limita ao mínimo de 0%
    // Atualiza a label da porcentagem na interface
    sprintf(convstr, "%.1f%%", gst->setPointPercentL2); // Converte o valor percentual em string com %
    lv_label_set_text(ui->ui_telaMain_lbSetL2, convstr); // Atualiza a label de porcentagem
    // Converte o valor percentual para tensão correspondente e exibe
    gst->setPointL2 = (gst->setPointPercentL2 * gst->vEscala) / 1000.0; // Calcula a tensão com base na porcentagem
    sprintf(convstr, "%.1f", gst->setPointL2); // Converte o valor de tensão em string
    //lv_label_set_text(ui->ui_telaMain_lbDisplayL2, convstr); // Atualiza a label de tensão
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Faz a conversão de porcentagem para tensao com base na escala selecionada, atribui o valor à variavel de tensao e atualiza as labels de porcentagem e tensao
void showSetPointL3(lv_ui *ui, STATUS_GST *gst) {
  char convstr[32];
  // Exibe o valor atual de porcentagem diretamente
  if (gst->setPointPercentL3 > SET_POINT_PERCENT_MAX) gst->setPointPercentL3 = SET_POINT_PERCENT_MAX; // Limita ao máximo
  if (gst->setPointPercentL3 < 0.0f) gst->setPointPercentL3 = 0.0f; // Limita ao mínimo de 0%
  // Atualiza a label da porcentagem na interface
  sprintf(convstr, "%.1f%%", gst->setPointPercentL3); // Converte o valor percentual em string com %
  lv_label_set_text(ui->ui_telaMain_lbSetL3, convstr); // Atualiza a label de porcentagem
  // Converte o valor percentual para tensão correspondente e exibe
  gst->setPointL3 = (gst->setPointPercentL3 * gst->vEscala) / 1000.0; // Calcula a tensão com base na porcentagem
  sprintf(convstr, "%.1f", gst->setPointL3); // Converte o valor de tensão em string
  //lv_label_set_text(ui->ui_telaMain_lbDisplayL3, convstr); // Atualiza a label de tensão
}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //Atualiza o valor das variaveis das tres fases, faz as conversões necessarias e atualiza os valores dos setpoints na tela ao mesmo tempo 
 void showSetPointsPercents(lv_ui *ui, STATUS_GST *gst){                   

   showSetPointL1(ui, gst);
   showSetPointL2(ui, gst);
   showSetPointL3(ui, gst);
   Serial.println("Valores atualizados com sucesso.");
 }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Guarda o valor atual dos setPoints de todas as fases (usada no desbloqueio do teclado)
void saveSetPointsPercents(lv_ui *ui, STATUS_GST *gst){
  gst->memSetPointL1 = gst->setPointPercentL1;
  gst->memSetPointL2 = gst->setPointPercentL2;
  gst->memSetPointL3 = gst->setPointPercentL3;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Restaura o valor das variáveis que foram salvas na memória no momento que o teclado foi desbloqueado (usada no bloqueio do teclado)  
void restoreSetPointsPercents(lv_ui *ui, STATUS_GST *gst){
  gst->setPointPercentL1 = gst->memSetPointL1;
  gst->setPointPercentL2 = gst->memSetPointL2;
  gst->setPointPercentL3 = gst->memSetPointL3;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Alterna o status do agrupamento de fases
void alternarGrupoFases(lv_ui *ui, STATUS_GST *gst){
  if(gst->atvGrupoFases){                                                          //Verifica se as fases estão agrupadas e alterna o agrupamento
    gst->atvGrupoFases = 0;
    ativarL1(ui, gst);                                                        //Torna fase 1 ativa (já altera as bordas individuais das fases)
    Serial.println("desagrupado");
    lv_label_set_text(ui->ui_telaMain_label_btnAgrupar, "Agrupar");         //Muda a label do botão de agrupar
    lv_obj_clear_flag(ui->ui_telaMain_btn_upL1, LV_OBJ_FLAG_HIDDEN);        //Mostra os botoes up/down L1 e L3
    lv_obj_clear_flag(ui->ui_telaMain_img_upL1, LV_OBJ_FLAG_HIDDEN);                                 
    lv_obj_clear_flag(ui->ui_telaMain_btn_downL1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui->ui_telaMain_img_downL1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui->ui_telaMain_btn_upL3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui->ui_telaMain_img_upL3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui->ui_telaMain_btn_downL3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui->ui_telaMain_img_downL3, LV_OBJ_FLAG_HIDDEN);
  }else{
    Serial.println("agrupado");
    gst->atvGrupoFases = 1;
    gst->atvL1 = 0;                                                                                   //Desativa as fases individualmente
    gst->atvL2 = 0;
    gst->atvL3 = 0;
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_L1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);       //Mostra as bordas dos containers de fase
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_L2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_L3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);   
    lv_label_set_text(ui->ui_telaMain_label_btnAgrupar, "Desagrupar");                              //Muda a label do botão de agrupar
    lv_obj_add_flag(ui->ui_telaMain_btn_upL1, LV_OBJ_FLAG_HIDDEN);                                  //Esconde os botoes up/down L1 e L3
    lv_obj_add_flag(ui->ui_telaMain_img_upL1, LV_OBJ_FLAG_HIDDEN);                                  
    lv_obj_add_flag(ui->ui_telaMain_btn_downL1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->ui_telaMain_img_downL1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->ui_telaMain_btn_upL3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->ui_telaMain_img_upL3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->ui_telaMain_btn_downL3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->ui_telaMain_img_downL3, LV_OBJ_FLAG_HIDDEN);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Incrementa o valor de porcentagem da(s) fase(s) selecionada(s) com base no passo selecionado 
void incPercent(enum PERCENTS_FASES fase, STATUS_GST *gst) {
    double passoLocal;
    // Determina o passo local com base no modo
    if (gst->modeVolt) { // Modo Tensão
        passoLocal = calcPassoTensao(gst->valPasso, gst->vEscala); // Chama a função calcPassoTensao
    } else { // Modo Percentual
        passoLocal = ((double)gst->valPasso) / 10; // Passo em modo Percentual
    }
    Serial.println(passoLocal);
    // Incremento com base na fase
    if (fase == PERCENT_FASE_L1) {
        gst->setPointPercentL1 += passoLocal; // Incrementa Fase L1
    } else if (fase == PERCENT_FASE_L2) {
        gst->setPointPercentL2 += passoLocal; // Incrementa Fase L2
    } else if (fase == PERCENT_FASE_L3) {
        gst->setPointPercentL3 += passoLocal; // Incrementa Fase L3
    } else { // Incrementa todas as fases
        gst->setPointPercentL1 += passoLocal;
        gst->setPointPercentL2 += passoLocal;
        gst->setPointPercentL3 += passoLocal;
    }
    // Validação dos limites máximos
    if (gst->setPointPercentL1 > SET_POINT_PERCENT_MAX) gst->setPointPercentL1 = SET_POINT_PERCENT_MAX;
    if (gst->setPointPercentL2 > SET_POINT_PERCENT_MAX) gst->setPointPercentL2 = SET_POINT_PERCENT_MAX;
    if (gst->setPointPercentL3 > SET_POINT_PERCENT_MAX) gst->setPointPercentL3 = SET_POINT_PERCENT_MAX;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Decrementa o valor de porcentagem da(s) fase(s) selecionada(s) com base no passo selecionado 
void decPercent(enum PERCENTS_FASES fase, STATUS_GST *gst) {
    double passoLocal;
    // Determina o passo local com base no modo
    if (gst->modeVolt) { // Modo Tensão
        passoLocal = calcPassoTensao(gst->valPasso, gst->vEscala); // Chama a função calcPassoTensao
    } else { // Modo Percentual
        passoLocal = ((double)gst->valPasso) / 10; // Passo em modo Percentual
    }
    Serial.println(passoLocal);
    // Decremento com base na fase
    if (fase == PERCENT_FASE_L1) {
        gst->setPointPercentL1 -= passoLocal; // Decrementa Fase L1
    } else if (fase == PERCENT_FASE_L2) {
        gst->setPointPercentL2 -= passoLocal; // Decrementa Fase L2
    } else if (fase == PERCENT_FASE_L3) {
        gst->setPointPercentL3 -= passoLocal; // Decrementa Fase L3
    } else { // Decrementa todas as fases
        gst->setPointPercentL1 -= passoLocal;
        gst->setPointPercentL2 -= passoLocal;
        gst->setPointPercentL3 -= passoLocal;
    }
    // Validação dos limites mínimos
    if (gst->setPointPercentL1 < 0.0f) gst->setPointPercentL1 = 0.0f;
    if (gst->setPointPercentL2 < 0.0f) gst->setPointPercentL2 = 0.0f;
    if (gst->setPointPercentL3 < 0.0f) gst->setPointPercentL3 = 0.0f;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Seta um valor fixo de porcentagem para a(s) fase(s) ativa(s) 
void setPercent(int valor, STATUS_GST *gst) {
  if(gst->atvGrupoFases){
    gst->setPointPercentL1 = valor;
    gst->setPointPercentL2 = valor;
    gst->setPointPercentL3 = valor;
  }else if (gst->atvL1){
    gst->setPointPercentL1 = valor;
  }else if (gst->atvL2){
    gst->setPointPercentL2 = valor;
  }else if (gst->atvL3){
    gst->setPointPercentL3 = valor;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Calcula o valor do passo na escala de tensão com base no valor do passo e escala selecionados 
double calcPassoTensao(double valPasso, double escala) {

    Serial.printf("escala %.f\r\n", escala);
    Serial.printf("valPasso %.f\r\n", valPasso);
    Serial.printf("result %.f\r\n", (valPasso * 100.0) / escala);
    // Cálculo do passo baseado em valPasso e na escala
    return (valPasso * 100.0) / escala; // Ajuste conforme a lógica desejada
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Bloqueia o teclado para que não seja inserido mais nenhum valor acidentamente em qualquer setPoint, além de atualizar o valor na tela se o teclado estiver ativo
void bloquearTeclado(lv_ui *ui, STATUS_GST *gst){

  if (tecladoHabilitado == true){
      tecladoHabilitado = false;
      // Resetar entrada 
      bufferIndex = 0; 
      isInputMode = false; // Sai do modo de entrada 
      altModeInputTeclado(ui, gst);
      memset(inputBuffer, 0, sizeof(inputBuffer));
      showSetPointsPercents(ui, gst);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Desbloqueia o teclado, permitindo ao usuario inserir o valor do setPoint manualmente
void desbloquearTeclado(lv_ui *ui, STATUS_GST *gst){
  // Ativar modo de entrada apenas pelo botão "OK" 
  Serial.println("Modo de entrada ativado."); 
  saveSetPointsPercents(ui, gst); //Salva os valores das fases
  isInputMode = true; 
  altModeInputTeclado(ui, gst); 
  bufferIndex = 0; 
  memset(inputBuffer, 0, sizeof(inputBuffer)); 
  tecladoHabilitado = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Função responsavel pelo fechamento automático da Message box
void mbox_close_event_cb(lv_event_t * e) {
    // Se o timer estiver ativo, cancela-o
    if(mbox_timer) {
      lv_timer_del(mbox_timer);
      mbox_timer = NULL;
    }
    active_mbox = NULL; // Reseta o ponteiro da message box
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Alternar modo das checkbox HabLN, altera as cores dos checkbox para deixar evidente seu status
void altModecbHab(lv_ui *ui, STATUS_GST *gst){
  if(gst-> habL1 == false){
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL1, lv_color_hex(0xd60020), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->ui_telaMain_cbHabL1, lv_color_hex(0xd60020), LV_PART_MAIN|LV_STATE_DEFAULT);
  }else{
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL1, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->ui_telaMain_cbHabL1, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(gst-> habL2 == false){
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL2, lv_color_hex(0xd60020), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->ui_telaMain_cbHabL2, lv_color_hex(0xd60020), LV_PART_MAIN|LV_STATE_DEFAULT);
  }else{
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL2, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->ui_telaMain_cbHabL2, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(gst-> habL3 == false){
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL3, lv_color_hex(0xd60020), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->ui_telaMain_cbHabL3, lv_color_hex(0xd60020), LV_PART_MAIN|LV_STATE_DEFAULT);
  }else{
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL3, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->ui_telaMain_cbHabL3, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
  }  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Alternar modo de input do teclado, altera as cores dos botões para deixar evidente o status do teclado
void altModeInputTeclado(lv_ui *ui, STATUS_GST *gst){
  if(isInputMode==false){
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n0, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n1, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n2, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n3, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n4, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n5, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n6, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n7, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n8, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n9, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_cancel, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_ok, lv_color_hex(0xecf713), LV_PART_MAIN|LV_STATE_DEFAULT);
  } else {
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n0, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n1, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n2, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n3, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n4, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n5, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n6, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n7, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n8, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n9, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_cancel, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_ok, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Atualiza os valores do dashboard (tensao, corrente e fator de potencia)
void ihmDashboardRefresh() {
  char convstr[32];
  lv_ui *ui = getUiTelaMain();
  STATUS_GST *gst = getPtrStatusGst();

  // Verifica se os ponteiros principais são válidos
  if (ui == nullptr) {
    Serial.println("Erro: Ponteiro ui nulo em ihmDashboardRefresh");
    return;
  }
  if (gst == nullptr) {
    Serial.println("Erro: Ponteiro gst nulo em ihmDashboardRefresh");
    return;
  }

  // Verifica cada objeto LVGL individualmente
  bool hasError = false;
  if (ui->ui_telaMain_lbDisplayL1 == nullptr) {
    Serial.println("Erro: ui_telaMain_lbDisplayL1 é nulo");
    hasError = true;
  }
  if (ui->ui_telaMain_lbDisplayL2 == nullptr) {
    Serial.println("Erro: ui_telaMain_lbDisplayL2 é nulo");
    hasError = true;
  }
  if (ui->ui_telaMain_lbDisplayL3 == nullptr) {
    Serial.println("Erro: ui_telaMain_lbDisplayL3 é nulo");
    hasError = true;
  }
  if (ui->ui_telaMain_lbCorrenteL1 == nullptr) {
    Serial.println("Erro: ui_telaMain_lbCorrenteL1 é nulo");
    hasError = true;
  }
  if (ui->ui_telaMain_lbCorrenteL2 == nullptr) {
    Serial.println("Erro: ui_telaMain_lbCorrenteL2 é nulo");
    hasError = true;
  }
  if (ui->ui_telaMain_lbCorrenteL3 == nullptr) {
    Serial.println("Erro: ui_telaMain_lbCorrenteL3 é nulo");
    hasError = true;
  }
  if (ui->ui_telaMain_lbFatorL1 == nullptr) {
    Serial.println("Erro: ui_telaMain_lbFatorL1 é nulo");
    hasError = true;
  }
  if (ui->ui_telaMain_lbFatorL2 == nullptr) {
    Serial.println("Erro: ui_telaMain_lbFatorL2 é nulo");
    hasError = true;
  }
  if (ui->ui_telaMain_lbFatorL3 == nullptr) {
    Serial.println("Erro: ui_telaMain_lbFatorL3 é nulo");
    hasError = true;
  }
  if (hasError) {
    Serial.println("Erro: Um ou mais objetos LVGL são nulos em ihmDashboardRefresh");
    return;
  }

  // Depuração dos valores brutos
  Serial.print("Valor bruto gst->tensaoL1: "); Serial.println(gst->tensaoL1);
  Serial.print("Valor bruto gst->tensaoL2: "); Serial.println(gst->tensaoL2);
  Serial.print("Valor bruto gst->tensaoL3: "); Serial.println(gst->tensaoL3);
  Serial.print("Valor bruto gst->correnteL1: "); Serial.println(gst->correnteL1);
  Serial.print("Valor bruto gst->correnteL2: "); Serial.println(gst->correnteL2);
  Serial.print("Valor bruto gst->correnteL3: "); Serial.println(gst->correnteL3);
  Serial.print("Valor bruto gst->fatorDePotenciaL1: "); Serial.println(gst->fatorDePotenciaL1);
  Serial.print("Valor bruto gst->fatorDePotenciaL2: "); Serial.println(gst->fatorDePotenciaL2);
  Serial.print("Valor bruto gst->fatorDePotenciaL3: "); Serial.println(gst->fatorDePotenciaL3);

  // Atualiza a label e o status do container de On/Off
  if(gst->statusOnOff){
    lv_label_set_text(ui->ui_telaMain_label_OnOff, "LIGADO");
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_label_OnOff, lv_color_hex(0x2fda64), LV_PART_MAIN|LV_STATE_DEFAULT);
  } else{
    lv_label_set_text(ui->ui_telaMain_label_OnOff, "DESLIGADO");
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_label_OnOff, lv_color_hex(0xff002D), LV_PART_MAIN|LV_STATE_DEFAULT);
  }

  // Atualiza os labels de tensão
  sprintf(convstr, "%.1f", (float)gst->tensaoL1);
  lv_label_set_text(ui->ui_telaMain_lbDisplayL1, convstr);
  sprintf(convstr, "%.1f", (float)gst->tensaoL2);
  lv_label_set_text(ui->ui_telaMain_lbDisplayL2, convstr);
  sprintf(convstr, "%.1f", (float)gst->tensaoL3);
  lv_label_set_text(ui->ui_telaMain_lbDisplayL3, convstr);

  // Atualiza os labels de corrente
  sprintf(convstr, "%.1f", (float)gst->correnteL1/10.0);
  lv_label_set_text(ui->ui_telaMain_lbCorrenteL1, convstr);
  sprintf(convstr, "%.1f", (float)gst->correnteL2/10.0);
  lv_label_set_text(ui->ui_telaMain_lbCorrenteL2, convstr);
  sprintf(convstr, "%.1f", (float)gst->correnteL3/10.0);
  lv_label_set_text(ui->ui_telaMain_lbCorrenteL3, convstr);

  // Atualiza os labels de fator de potência
  sprintf(convstr, "%.2f", (float)gst->fatorDePotenciaL1 / 100.0);
  lv_label_set_text(ui->ui_telaMain_lbFatorL1, convstr);
  sprintf(convstr, "%.2f", (float)gst->fatorDePotenciaL2 / 100.0);
  lv_label_set_text(ui->ui_telaMain_lbFatorL2, convstr);
  sprintf(convstr, "%.2f", (float)gst->fatorDePotenciaL3 / 100.0);
  lv_label_set_text(ui->ui_telaMain_lbFatorL3, convstr);

  Serial.println("Dashboard atualizado com sucesso");
}
//*****************************************************************************
// Inicialização dos eventos da telaMain
//*****************************************************************************
void events_init_ui_telaMain(lv_ui *ui) {
    lv_obj_add_event_cb(ui->ui_telaMain_dashboard, ui_telaMain_event_handler, LV_EVENT_SCREEN_LOADED, ui); // LV_EVENT_ALL
    //lv_obj_add_event_cb(ui->ui_telaMain_btnOnOff, ui_telaMain_btn_onoff_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_cont_L1, ui_telaMain_container_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_cont_L2, ui_telaMain_container_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_cont_L3, ui_telaMain_container_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_cbHabL1, ui_telaMain_container_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_cbHabL2, ui_telaMain_container_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_cbHabL3, ui_telaMain_container_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_upL1, ui_telaMain_btn_updown_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_upL2, ui_telaMain_btn_updown_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_upL3, ui_telaMain_btn_updown_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_downL1, ui_telaMain_btn_updown_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_downL2, ui_telaMain_btn_updown_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_downL3, ui_telaMain_btn_updown_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_sliderFreq, ui_telaMain_container_frequency_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnFreq50, ui_telaMain_container_frequency_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnFreq60, ui_telaMain_container_frequency_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selPasso1, ui_telaMain_container_passo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selPasso2, ui_telaMain_container_passo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selPasso3, ui_telaMain_container_passo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selPasso4, ui_telaMain_container_passo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selModePercent, ui_telaMain_container_mode_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selModeGrandeza, ui_telaMain_container_mode_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnPercent1, ui_telaMain_btn_percent_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnPercent2, ui_telaMain_btn_percent_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnPercent3, ui_telaMain_btn_percent_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnPercent4, ui_telaMain_btn_percent_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnPercent5, ui_telaMain_btn_percent_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnAgrupar, ui_telaMain_container_modegrupo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnNominal, ui_telaMain_container_modegrupo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnConfig, ui_telaMain_container_modegrupo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selEscala0, ui_telaMain_container_scale_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selEscala1, ui_telaMain_container_scale_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selEscala2, ui_telaMain_container_scale_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selEscala3, ui_telaMain_container_scale_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selEscala4, ui_telaMain_container_scale_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selEscala5, ui_telaMain_container_scale_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selEscala6, ui_telaMain_container_scale_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_selEscala7, ui_telaMain_container_scale_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_label_seq_l1, ui_telaMain_btn_seq_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_label_seq_l2, ui_telaMain_btn_seq_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_label_seq_l3, ui_telaMain_btn_seq_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnSeqL1L2, ui_telaMain_btn_seq_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnSeqL2L3, ui_telaMain_btn_seq_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnSeqL1L3, ui_telaMain_btn_seq_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btnSeqL1L2L3, ui_telaMain_btn_seq_fase_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n0, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n1, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n2, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n3, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n4, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n5, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n6, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n7, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n8, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_n9, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_ok, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_telaMain_btn_cancel, ui_telaMain_btn_teclado_event_handler, LV_EVENT_ALL, ui);
}
//=============================================================================
void eventsInit() {
    // Inicialização de eventos, se necessário
}

void eventsTask() {
    // Tarefas periódicas de eventos, se necessário
}
