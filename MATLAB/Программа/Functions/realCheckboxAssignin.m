% --- Создание графиков и привязка их к определенным чекбоксам для
% эталонных данных
function realCheckboxAssignin(Real)
real.ch1.coordinate = plot(Real.t(:),Real.x(:),'--og','Visible','off','DisplayName', 'x');
real.ch1.speed = plot(Real.t(:),Real.Vx(:),'--og','Visible','off','DisplayName', 'V(x)');
real.ch1.acceleration = plot(Real.t(:),Real.ax(:),'--og','Visible','off','DisplayName', 'a(x)');

real.ch2.coordinate = plot(Real.t(:),Real.y(:),'--or','Visible','off','DisplayName', 'y');
real.ch2.speed = plot(Real.t(:),Real.Vy(:),'--or','Visible','off','DisplayName', 'V(y)');
real.ch2.acceleration = plot(Real.t(:),Real.ay(:),'--or','Visible','off','DisplayName', 'a(y)');

real.ch3.coordinate = plot(Real.t(:),Real.z(:),'--ob','Visible','off','DisplayName', 'z');
real.ch3.speed = plot(Real.t(:),Real.Vz(:),'--ob','Visible','off','DisplayName', 'V(z)');
real.ch3.acceleration = plot(Real.t(:),Real.az(:),'--ob','Visible','off','DisplayName', 'a(z)');

legendOff();

assignin('base','realPlot',real);
