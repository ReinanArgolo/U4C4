# Projeto: Interrupções no RP2040 com BitDogLab  

## Descrição  
Este projeto tem como objetivo consolidar os conceitos sobre interrupções em microcontroladores, explorando o uso da placa de desenvolvimento **BitDogLab** e sua integração com **LEDs WS2812, um LED RGB e botões**.  

## Funcionalidades Implementadas  
1. O **LED vermelho** do LED RGB pisca continuamente **5 vezes por segundo**.  
2. O **Botão A** incrementa o número exibido na matriz de LEDs (0–9).  
3. O **Botão B** decrementa o número exibido na matriz de LEDs (0–9).  
4. A **matriz de LEDs WS2812** exibe números de 0 a 9 em um formato fixo ou criativo.  

## Componentes Utilizados  
- **Microcontrolador RP2040** (Placa BitDogLab)  
- **Matriz 5x5 de LEDs WS2812** (GPIO 7)  
- **LED RGB** (GPIOs 11, 12 e 13)  
- **Botão A** (GPIO 5)  
- **Botão B** (GPIO 6)  

## Requisitos Técnicos  
- **Uso de Interrupções (IRQ)** para capturar os eventos dos botões.  
- **Debouncing via Software** para evitar leituras erradas nos botões.  
- **Controle de LEDs** comuns e endereçáveis para reforçar o aprendizado.  
- **Código bem estruturado e comentado** para facilitar a compreensão.  

## Execução do Projeto  
1. **Configurar** a placa BitDogLab com o firmware adequado.  
2. **Transferir o código** para a placa via USB.  
3. **Executar** o código e testar os botões e LEDs.  

## Vídeo de Demonstração  
🎥 [Acesse o vídeo aqui](https://youtube.com/shorts/hYcqrcT9VJc?feature=share) 

## Autor  
Reinan Argolo
