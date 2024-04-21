<h1>
  Контроллер пневмоподвески на Arduino <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/e/e0/ArduinoLogo_%C2%AE.svg/105px-ArduinoLogo_%C2%AE.svg.png"/>
</h1> 
<h3>В данном репозитории изложена моя реализация контроллера клапанами пневмоподвески</h3>    
Данный проект был вдохновлен моим знакомым которому я его и делал.<br>
Тут я постараюсь максимально просто изложить суть этой штуки, так что бы вы смогли сами ее повторить. Для этого вам понадобиться небольшой навык владения паяльником, какойто уровень владения компьютером который вам позволит установить программу Arduino IDE и залить через нее прошивку из этого репозитория.
<h3>Если в крации то контроллер состоит из трех вещей:</h3>
<ul>
  <li>Сам контроллер Arduino Nano, который работает с джоистиком и релюхами</li>
  <li>Модуль с реле которые управляют клапанами спуска и подъема</li>
  <li>Джоистик от Dendy</li>
</ul>
<h2>Что за файлы в данном репозитории:</h2>
<ul>
  <li><a href="https://github.com/Stifler33/Controller-Car-Suspension/blob/main/DendyGamepad.ino">DendyGamepad.ino</a> - это сам файл прошивки для контроллера Arduino Nano. Что можно в нем редактировать постараюсь описать</li>
  <li><a href="https://github.com/Stifler33/Controller-Car-Suspension/blob/main/8Ch-relay.pdf">8Ch-relay.pdf</a> - это описание модуля с реле. Он нужен больше для тех кто шарит))</li>
  <li><a href="https://github.com/Stifler33/Controller-Car-Suspension/blob/main/Schematic_car_suspension.pdf">Schematic_car_suspension.pdf</a> - это электронная принципиальная схема.</li>
  <li><a href="https://github.com/Stifler33/Controller-Car-Suspension/blob/main/connection%20relay%20module.pdf">connection relay module.pdf</a> - это схема подключения клапанов к блоку реле</li>
</ul>
<h2>Важно !!! <img src="https://media1.tenor.com/m/ZFDl8QBRzCUAAAAC/warn-warning.gif" height="80"/></h2>
<h3>Блоки реле бывают двух видов:</h3>
<ul>
  <li>У первых питание реле идет от 12 вольт</li>
  <li>У вторых питание идет от 5 вольт</li>
</ul>
Что бы отличить что есть что, надо посмотреть маркировку на самих реле - там будет либо 12VDC либо 5VDC соответственно.<br>
От этого зависит какое напряжение надо подавать на кондакт JD-VCC модуля реле. Этот контакт расположен на гребенке из трех штырьков с права. На схема это J3 3-й контакт.<br>
Также ОЧЕНЬ важно поставить защитные диоды как на схеме <a href="https://github.com/Stifler33/Controller-Car-Suspension/blob/main/connection%20relay%20module.pdf">connection relay module.pdf</a> они стоят между контактом на клапан и землей. Если их не поставть то контроллер будет постоянно зависать !!!<br>

