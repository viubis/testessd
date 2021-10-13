#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include <unistd.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <locale.h>
// #define ADDRESS     "tcp://localhost:1883"
//...................................................................
//... ADRESS
//...................................................................
#define ADDRESS     "ssl://b0b1b4c6d9b148d7bc0f4c535f24c67a.s1.eu.hivemq.cloud:8883" 
#define ID          "RASPBERRY"

#define QOS            2
#define TIMEOUT        10000L
#define KEEP_ALIVE     60
#define CLOCKS_PER_SEC 1

volatile MQTTClient_deliveryToken deliveredtoken;

//Entradas Switchs e buttons
#define SWITCH_PRESENCA_SALA 4 
#define SWITCH_PRESENCA_GARAGEM 17
#define SWITCH_PRESENCA_INTERNO 27
#define SWITCH_ALARME 22
#define BUTTON_PORTA 5
#define BUTTON_JANELA 19


// ESTADOS
typedef struct {
	int estado_atual;
	int temp_atual;
	int temp_min;
	int temp_max;
	int alterar_operacao_default;
	int tempo_ausencia_pessoas;
} AC;

typedef struct {
	int estado_atual;
} Alarme;

typedef struct {
	int estado_atual;
	int hora_minima;
	int hora_maxima;
} Jardim;

typedef struct {
	int estado_atual;
	int hora_minima;
	int hora_maxima;
} Garagem;

typedef struct {
	int estado_atual;
} LuzInterna;

typedef struct {
	AC ac;
	Alarme alarme;
	Jardim jardim;
	Garagem garagem;
	LuzInterna luzInterna;
	bool automacaoTOGGLE;
} Components;


// VARIÁVEIS GLOBAIS
int TEMPERATURA_EXTERNA;
bool MENSAGEM_RECEBIDA = false;
Components comp


//verifica alterações na entrada
bool alteracao(int presenca_sala,int presenca_garagem,int presenca_interno,int switch_alarme,int janela,int porta){
	
	int estado_presenca_garagem, estado_presenca_interna, estado_presenca_sala, estado_alarme, estado_porta, estado_janela;
	
	if(presenca_sala != estado_presenca_sala){
		estado_presenca_sala = presenca_sala;
		printf("sala\n");
		return true;
	}
	if(presenca_garagem != estado_presenca_garagem){
		estado_presenca_garagem = presenca_garagem;
		printf("garagem\n");
		return true;
	}
	if(presenca_interno != estado_presenca_interna){
		estado_presenca_interna = presenca_interno;
		printf("interno\n");
		return true;
	}
	if(switch_alarme != estado_alarme){
		estado_alarme = switch_alarme;
		printf("alarme\n");
		return true;
	}
	if(janela != estado_janela){
		estado_janela = janela;
		printf("janela\n");
		return true;
	}
	if(porta != estado_porta){
		estado_porta = porta;
		printf("porta\n");
		return true;
	}

	return false;
}
  
 //funcao pra ativamento dos sistemas
void ativamento(int presenca_sala,int presenca_garagem,int presenca_interno,int switch_alarme,int janela,int porta){

}	

int main() {
  MQTTClient client;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  MQTTClient_deliveryToken token;

//CONF PINOS
	wiringPiSetupGpio () ;

	pinMode (SWITCH_PRESENCA_SALA, INPUT) ;
	pinMode (SWITCH_PRESENCA_GARAGEM, INPUT) ;
	pinMode (SWITCH_PRESENCA_INTERNO, INPUT) ;
	pinMode (SWITCH_ALARME, INPUT) ;
	pinMode (BUTTON_PORTA, INPUT) ;
	pinMode (BUTTON_JANELA, INPUT) ;

    printf ("pinos de botão foram configurados. \n") ;
//fim conf pinos	



  // char *topic = NULL;
  // int topic_len;
  // MQTTClient_message *receive_msg = NULL;
  // char *ptr = NULL;

  /*do{
      scanf("%s", buffer);

      if(strcmp("q", buffer) != 0){
        publishMessage(client, &token, "JARDIM/LUZ", buffer);
      }

  } while(strcmp("q", buffer) != 0); */

  while(true){

		if(alteracao( digitalRead(SWITCH_PRESENCA_SALA), digitalRead(SWITCH_PRESENCA_GARAGEM),digitalRead(SWITCH_PRESENCA_INTERNO),
								digitalRead(SWITCH_ALARME),digitalRead(BUTTON_JANELA),digitalRead(BUTTON_PORTA)) == true || MENSAGEM_RECEBIDA){
		//if((horarioAtual_ATUALIZOU) || (temPessoas_ALARME) || (temPessoas_GARAGEM) || (temPessoas_AC) || (portaJarnelaAbertas_ALARME) || (MENSAGEM_RECEBIDA)){

			//alarme(temPessoas_ALARME, portaJarnelaAbertas_ALARME);
      		//publishMessage(client, &token, "ALARME/VALOR", comp.alarme.estado_atual);

			//iluminacaoAmbientesInternos(temPessoas_INTERNO);
      		//publishMessage(client, &token, "INTERNO/ILUMINACAO/VALOR", comp.luzInterna.estado_atual);

			//iluminacaoGaragem(horario_ATUAL, temPessoas_GARAGEM);
      		//publishMessage(client, &token, "GARAGEM/ILUMINACAO/VALOR", comp.garagem.estado_atual);

			//iluminacaoJardim(horario_ATUAL);
      		//publishMessage(client, &token, "JARDIM/ILUMINACAO/VALOR", comp.jardim.estado_atual);

			//arCondicionado(temPessoas_AC);
      		//publishMessage(client, &token, "AC/TEMPERATURA/VALOR", comp.ac.estado_atual);

			//horarioAtual_ATUALIZOU = false;
      		//MENSAGEM_RECEBIDA = false;
			  printf("entrou no if \n");
		}
	}

}
