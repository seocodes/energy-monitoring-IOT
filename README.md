# 📊 **Projeto de Monitoramento de Energia IoT** ⚡

Este projeto tem como objetivo monitorar os parâmetros de **tensão**, **corrente** e **potência** de um circuito elétrico, utilizando sensores e enviando os dados para o Firebase. Além disso, as informações também são exibidas em um display OLED e disponibilizadas em tempo real através de um site minimalista.

---

## 🔎 **Sumário**  

1. [Introdução](#introdução)
2. [Requisitos do Projeto](#requisitos-do-projeto)
3. [Funcionamento do Sistema](#funcionamento-do-sistema)
4. [Como Rodar o Projeto](#como-rodar-o-projeto)
5. [Visualização dos Dados](#visualização-dos-dados)
6. [Referências](#referências)

---

## 📝 **Introdução**  
O objetivo deste projeto é monitorar os parâmetros elétricos de um sistema, utilizando sensores para coletar os valores de tensão (V), corrente (A) e potência (kW), e exibi-los tanto em um display OLED quanto em uma página web. Todos os dados coletados são enviados para o **Firebase**, permitindo a consulta em tempo real de qualquer lugar.

Este projeto é ideal para quem está aprendendo a trabalhar com sensores, Firebase e integração com displays OLED.

---

## 🛠️ **Requisitos do Projeto**

### Hardware Necessário:
- **ESP32** (ou similar)
- **Sensor de Corrente** (ex: ACS712)
- **Sensor de Tensão** (ex: ZMPT101B)
- **Display OLED** (modelo 128x64)
- **Cabos e Protoboard**

### Software Necessário:
- **Arduino IDE** com suporte para o ESP32
- **Bibliotecas**:
  - WiFi.h
  - Firebase_ESP_Client.h
  - Adafruit_GFX.h
  - Adafruit_SSD1306.h

---

## ⚙️ **Funcionamento do Sistema**

### 📡 **Coleta de Dados**  
O ESP32 se conecta à rede Wi-Fi e ao Firebase, onde coleta e envia os dados dos sensores de corrente e tensão. Os valores de corrente e tensão são lidos a partir dos pinos analógicos conectados aos sensores.

### 💡 **Cálculo de Potência**  
A potência é calculada multiplicando a tensão pela corrente e dividindo o resultado por 1000 para obter o valor em **kW**.

### 🖥️ **Display OLED**  
Os valores de tensão, corrente e potência são exibidos em um **display OLED 128x64**, proporcionando uma visualização local dos dados.

### 🔄 **Atualização em Tempo Real**  
Além de exibir os valores no display, os dados são enviados ao **Firebase** e também são acessíveis em tempo real via um site minimalista.

---

## 🏃‍♂️ **Como Rodar o Projeto**

1. **Configuração do Firebase**:
   - Crie um novo projeto no [Firebase](https://console.firebase.google.com/).
   - Ative o Realtime Database e obtenha a chave de autenticação da API.
   - Configure o código com as credenciais do Firebase, Wi-Fi e display OLED.

2. **Carregue o Código no ESP32**:
   - Utilize a Arduino IDE para carregar o código para o seu ESP32.
   - Verifique a conectividade Wi-Fi e o envio dos dados ao Firebase.

3. **Exibindo os Dados**:
   - O display OLED irá mostrar os valores de tensão, corrente e potência.
   - Acesse os dados em tempo real através do [site](https://energy-monitoring-iot.vercel.app/).

---

## 🌐 **Visualização dos Dados**

### 🖥️ **Página Web Minimalista**  
Os dados de tensão, corrente e potência podem ser visualizados através de um **site minimalista**, onde os valores são exibidos de forma simples e clara. Você pode acessar o site em tempo real aqui:  
[**Acessar o Site de Monitoramento**](https://energy-monitoring-iot.vercel.app/)

---

## 📚 **Referências**

- [Apresentação do Projeto no Canva](https://www.canva.com/design/DAGW2VyW358/ajvgcnhSi_5Qe643pKyY6Q/edit?utm_content=DAGW2VyW358&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)
- [Site de Monitoramento de Energia IoT](https://energy-monitoring-iot.vercel.app/)

---

### ⚡ **Projeto desenvolvido por:**
_Projeto de Monitoramento de Energia IoT com ESP32, Firebase e Display OLED_.
