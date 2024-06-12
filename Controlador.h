#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "Carrinho.h"
#include <cstdio>
#include <string.h>


class Controlador {
    private: 
        #define TAMANHO_MEMORIA 8

        // Comandos recebidos externamente
        typedef enum Comando {
            COM_PARAR = '0',
            COM_ANDAR_FRENTE = '1',
            COM_ANDAR_TRAS = '2',
            COM_VIRAR_HORARIO = '3',
            COM_VIRAR_ANTI_HORARIO = '4',
            COM_MUDAR_VELOCIDADE = 'v',
            COM_FIM = ';',
            COM_LIGAR_ESFREGAO = '5',
            COM_LIGAR_ESFREGAO_ANTI = '6',
            COM_DESLIGAR_ESFREGAO = '7',
            COM_ABRIR_TORNEIRA = '8',
            COM_FECHAR_TORNEIRA = '9'

        } Comando;

        // Possíveis estados que o Controlador pode ocupar como um autômato finito, 
        typedef enum EstadoControlador {
            INICIAL,
            LENDO_VELOCIDADE
        } EstadoControlador ;

        // Estado atual do Controlador
        EstadoControlador estadoControlador = INICIAL;

        // Memoria para salvar dados do automato
        char memoria[TAMANHO_MEMORIA] = {};

        // Referência ao carrinho que ele vai controlar
        Carrinho *carrinho;

        // * Operações com a memoria do automato *

        // Limpa a memória
        void limparMemoria() {
            memoria[0] = '\0';
        }

        // Adiciona o caracter lido na memória
        void salvarNaMemoria(char conteudo) {
            // Encontra o final do buffer
            int i = 0;
            while (i < 8 && memoria[i] != '\0') {
                i++;
            }
            if (i >= 8) {
                // Erro
            }

            // Salva o conteudo 
            memoria[i] = conteudo;

            // Atualiza o final da memoria
            if (i < 7) {
                memoria[i+1] = '\0';
            }
        }

        int lerNumeroMemoria() {
            int resultado;
            sscanf(memoria, "%d", &resultado);
            return resultado;
        }

    public:
        Controlador() {}

        Controlador(Carrinho *carrinho) {
            anexarCarrinho(carrinho);
        }

        void anexarCarrinho(Carrinho *carrinho) {
            this->carrinho = carrinho;
        }

        // Função para o autômato interpretar a entrada de ordens
        void interpretarOrdens(byte entrada) {
            switch (estadoControlador) {

                // Estado Inicial
                case INICIAL:
                    switch (entrada) {

                        // Ação Parar 
                        case COM_PARAR:
                            carrinho->setParado();
                            break;

                        // Ação Andar para Frente
                        case COM_ANDAR_FRENTE:
                            carrinho->setFrente();
                            break;

                        // Ação Andar para Tras
                        case COM_ANDAR_TRAS:
                            carrinho->setTras();
                            break;

                        // Ação Virar sentido Horário
                        case COM_VIRAR_HORARIO:
                            carrinho->setVirarHorario();
                            break;

                        // Ação Virar Anti Horário
                        case COM_VIRAR_ANTI_HORARIO:
                            carrinho->setVirarAntiHorario();
                            break;

                        // Ir para o estado Lendo Velocidade
                        case COM_MUDAR_VELOCIDADE:
                            estadoControlador = LENDO_VELOCIDADE;
                            limparMemoria();
                            break;

                        // Ligar esfregão
                        case COM_LIGAR_ESFREGAO:
                            carrinho->enableEsfregao();
                            break;

                        // Desligar esfregão
                        case COM_DESLIGAR_ESFREGAO:
                            carrinho->disableEsfregao();
                            break;

                        // Ligar esfregão anti-horário
                        case COM_LIGAR_ESFREGAO_ANTI:
                            carrinho->enableEsfregaoHorario();
                            break;

                        // Abrir torneira
                        case COM_ABRIR_TORNEIRA:
                            carrinho->abrirTorneira();
                            break;

                        // Fechar torneira
                        case COM_FECHAR_TORNEIRA:
                            carrinho->fecharTorneira();
                            break;
                    } 
                    break;

                // Estado Lendo Velocidade
                case LENDO_VELOCIDADE:

                    // Enquanto entrada for número, salve-o no buffer
                    if ('0' <= entrada && entrada <= '9') {
                        salvarNaMemoria(entrada);                        
                        
                    // Quando for fim de entrada
                    } else if (entrada == COM_FIM) {
                        // Muda a velocidade
                        int velocidade = lerNumeroMemoria();
                        carrinho->setVelocidade(velocidade);

                        limparMemoria();

                        // Volta para o estado Inicial
                        estadoControlador = INICIAL;
                    }
                    break;
            }
        }
};

#endif
