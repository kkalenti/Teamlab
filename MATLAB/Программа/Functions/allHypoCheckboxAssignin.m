% --- Создание графиков и привязка их к определенным чекбоксам для
% гипотез
function allHypoCheckboxAssignin(Hypo)

hypoSize = size(Hypo);
cmap = hsv(hypoSize(2)*9);
for i = 1:hypoSize(2)
    hypo(i).ch1.coordinate = plot(Hypo(i).t(:),Hypo(i).x(:),'-o','Color',cmap(i*7,:),...
        'Visible','off','DisplayName', 'Гипотеза x');
    hypo(i).ch1.speed = plot(Hypo(i).t(:),Hypo(i).Vx(:),'-o','Color',cmap(i*7,:),...
        'Visible','off','DisplayName', 'Этолон V(x)');
    hypo(i).ch1.acceleration = plot(Hypo(i).t(:),Hypo(i).ax(:),'-o','Color',cmap(i*7,:),...
        'Visible','off','DisplayName', 'Гипотезаa(x)');

    hypo(i).ch2.coordinate = plot(Hypo(i).t(:),Hypo(i).y(:),'-o','Color',cmap(i*8,:),...
        'Visible','off','DisplayName', 'Гипотеза y');
    hypo(i).ch2.speed = plot(Hypo(i).t(:),Hypo(i).Vy(:),'-o','Color',cmap(i*8,:),...
        'Visible','off','DisplayName', 'Гипотеза V(y)');
    hypo(i).ch2.acceleration = plot(Hypo(i).t(:),Hypo(i).ay(:),'-o','Color',cmap(i*8,:),...
        'Visible','off','DisplayName', 'Гипотеза a(y)');

    hypo(i).ch3.coordinate = plot(Hypo(i).t(:),Hypo(i).z(:),'-o','Color',cmap(i*9,:),...
        'Visible','off','DisplayName', 'Гипотеза z');
    hypo(i).ch3.speed = plot(Hypo(i).t(:),Hypo(i).Vz(:),'-o','Color',cmap(i*9,:),...
        'Visible','off','DisplayName', 'Гипотеза V(z)');
    hypo(i).ch3.acceleration = plot(Hypo(i).t(:),Hypo(i).az(:),'-o','Color',cmap(i*9,:),...
        'Visible','off','DisplayName', 'Этaлон a(z)');
end

legend Off;

assignin('base','hypoPlot',hypo);

