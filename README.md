# Embrace IoT — Monitoramento de Condições Climáticas de Risco

A Embrace cria um hub digital único que integra todos os atores envolvidos na resposta a eventos extremos — ONGs, coletivos, voluntários e as próprias comunidades afetadas. Em vez de esforços dispersos, toda a comunicação, cadastro de demandas e oferta de recursos flui por uma só interface, garantindo que cada campanha ou chamado de socorro seja imediatamente visível a quem estiver disponível para ajudar, reduzindo lacunas e sobreposições.

Este projeto representa o braço de monitoramento climático por IoT da solução Embrace. Ele é voltado à detecção antecipada de condições ambientais de risco em áreas urbanas — como chuvas intensas e alta umidade do solo — que podem agravar situações de vulnerabilidade.


Por meio de sensores conectados a uma ESP32, os dados de temperatura, umidade do ar, umidade do solo e presença de chuva são coletados continuamente e enviados via protocolo MQTT para um painel visual no Node-RED. Essa estrutura permite a visualização em tempo real e auxilia na tomada de decisões rápidas e coordenadas pelos atores envolvidos nas respostas emergenciais.

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

```
/
├── circuit/
│   ├── sketch.ino → Código principal do ESP32
│   ├── diagram.json → Arquivo do circuito no Wokwi
│   └── libraries.txt → Lista de bibliotecas utilizadas
├── node-red/
│   └── flow_node-red.json → Fluxo exportado do Node-RED
├── README.md → Documentação do projeto
```

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
