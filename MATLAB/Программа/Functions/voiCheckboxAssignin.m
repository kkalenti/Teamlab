% --- Создание графиков и привязка их к определенным чекбоксам для
% данных ВОИ
function voiCheckboxAssignin(VOI)
voi.ch1.coordinate = plot(VOI.t(:),VOI.x(:),'-*g','Visible','off','DisplayName', 'x');
voi.ch1.speed = plot(VOI.t(:),VOI.Vx(:),'-*g','Visible','off','DisplayName', 'V(x)');
voi.ch1.acceleration = plot(VOI.t(:),VOI.ax(:),'-*g','Visible','off','DisplayName', 'a(x)');

voi.ch2.coordinate = plot(VOI.t(:),VOI.y(:),'-*r','Visible','off','DisplayName', 'y');
voi.ch2.speed = plot(VOI.t(:),VOI.Vy(:),'-*r','Visible','off','DisplayName', 'V(y)');
voi.ch2.acceleration = plot(VOI.t(:),VOI.ay(:),'-*r','Visible','off','DisplayName', 'a(y)');

voi.ch3.coordinate = plot(VOI.t(:),VOI.z(:),'-*b','Visible','off','DisplayName', 'z');
voi.ch3.speed = plot(VOI.t(:),VOI.Vz(:),'-*b','Visible','off','DisplayName', 'V(z)');
voi.ch3.acceleration = plot(VOI.t(:),VOI.az(:),'-*b','Visible','off','DisplayName', 'a(z)');

legendOff();

assignin('base','voiPlot',voi);