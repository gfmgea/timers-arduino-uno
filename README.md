# Este projeto visa o melhor entendimento no tratamento de interrupções/timers do Arduino Uno.

Neste projeto foi programado uma interrupção externa no modo contador para contagem de 10 eventos através de um botão e, quando chegar ao 10° evento, o buzzer irá tocar 2 vezes.

Além disso, no timer0 foi programado uma contagem regressiva dem inutos e segundos, sendo o botão 1 adicionando um minuto até o máximo de 10min e o botão 2 iniciando/parando a contagem. Ao chegar em 0, o buzzer irá tocar 3 vezes.

Por fim, no timer1 foi programado o sistema de UP-TIME do sistema, realizando a contagem do tempo de funcionamento do programa.

Para mostrar esses dados, foi utilizado um LCD 16x2. Todas as ligações feitas estão ilustradas na imagem do circuito simulada em TinkerCad.


# This project aims at a better understanding of the handling of interrupts/timers on the Arduino Uno.

In this project, an external interruption was programmed in counter mode to count 10 events through a button and, when reaching the 10th event, the buzzer will ring twice.

In addition, timer0 has been programmed to count down minutes and seconds, with button 1 adding one minute to a maximum of 10 minutes and button 2 starting/stopping the countdown. Upon reaching 0, the buzzer will ring 3 times.

Finally, the UP-TIME system of the system was programmed on timer1, counting the running time of the program.

To show this data, a 16x2 LCD was used. All connections made are illustrated in the circuit image simulated in TinkerCad.
