# Embrace IoT — Monitoramento de Condições Climáticas de Risco

Este projeto faz parte da solução Embrace, voltada à detecção de condições climáticas que oferecem risco à população em áreas urbanas. A integração IoT permite a coleta, análise e visualização de dados como temperatura, umidade do ar, umidade do solo e presença de chuva.

Através de sensores conectados a uma ESP32, os dados são enviados via protocolo MQTT para um painel visual em Node-RED, possibilitando tomada de decisões em tempo real.

⚡ **Circuito Montado:**

![image](https://github.com/user-attachments/assets/b4197fe6-85be-4e53-b11d-55deee0d3135)

📦 **Componentes Utilizados**

- ESP32 DevKit V1 (Simulado no Wokwi)
- Sensor DHT22 (Temperatura e Umidade do Ar)
- Potenciômetro (Simulando sensor de umidade do solo)
- Botão (Simulando sensor de chuva)
- LED vermelho (Sinalizador de emergência)

🌐 **Tecnologias Aplicadas**

- Wokwi (Simulador de circuito IoT)
- Node-RED (Gateway e Dashboard)
- MQTT (Comunicação via broker HiveMQ)
- JSON (Formato das mensagens)
- Arduino Framework (Linguagem C++)

📊 **Funcionalidades**

- Coleta contínua dos dados climáticos:
  - Temperatura (°C)
  - Umidade do Ar (%)
  - Umidade do Solo (%)
  - Estado da Chuva (Sim/Não)
- Processamento lógico:
  - Define se há situação de PERIGO com base nos seguintes critérios:
    - Umidade > 85%
    - Umidade do solo > 80%
    - Chuva detectada (botão pressionado)
- Ação de emergência:
  - LED vermelho acende automaticamente em caso de PERIGO
- Envio dos dados via MQTT em tempo real
- Visualização dos dados no painel Node-RED

📡 **Estrutura MQTT**

- Broker utilizado: HiveMQ (broker.hivemq.com)  
- Porta: 1883  
- Topico de publicação: /embrace/sensores  

Formato da mensagem JSON enviada:

```json
{
  "temperatura": 32.0,
  "umidade": 90.0,
  "chuva": "SIM",
  "umidade_solo": 82,
  "alerta": "PERIGO"
}
```

🖥️ **Dashboard Node-RED**

Os dados recebidos são processados e exibidos em tempo real em gauges e textos:

- Temperatura (gauge circular)
- Umidade do ar (gauge circular)
- Umidade do solo (gauge circular)
- Estado da chuva (texto)
- Nível de risco (texto)

Fluxo do Node-RED:

MQTT in → JSON → [Debug, Dashboard Gauges e Texts]

📁 **Estrutura do Projeto**

├── sketch.ino → Código principal do ESP32

├── diagram.json → Arquivo do circuito no Wokwi

├── libraries.txt → Lista de bibliotecas utilizadas

├── flow_node_red.json → Fluxo exportado do Node-RED

└── /images → Imagens do circuito e dashboard


▶️ **Instruções de Execução**

Acesse o circuito no Wokwi:  
👉 https://wokwi.com/projects/432965765299127297

Clique em "Start Simulation"

No Node-RED:

Configure o broker para: broker.hivemq.com:1883

Importe o flow_node_red.json no editor

Acesse o painel: http://localhost:1880/ui

Visualize as leituras e o status de alerta em tempo real:

![image](https://github.com/user-attachments/assets/b0121f56-fa4a-44bc-8dca-269e8e5f5d1a)

🧪 **Testes**

Você pode testar diferentes cenários:

- Alterando a temperatura e umidade no DHT22 (via propriedades no Wokwi)
- Girando o potenciômetro (umidade do solo)
- Segurando o botão (simula chuva)

🎥 **Demonstração em Vídeo**

📺 Link do vídeo:

---

👨‍💻 **Integrantes**

Time Embrace – GS 2025-1:

- **Enzo Giuseppe Marsola** – RM: 556310, Turma: 2TDSPK  
- **Rafael de Souza Pinto** – RM: 555130, Turma: 2TDSPY  
- **Luiz Paulo F. Fernandes** – RM: 555497, Turma: 2TDSPF

📌 **Observações**

O projeto é totalmente funcional e pode ser executado em ambiente real substituindo o Wokwi por hardware físico
