% --- Создается пустая цель шума
function make3D(Info,content)

if (content == 2)
    poi3dPlot = plot3(Info.x,Info.y,Info.z,'+','LineWidth',2,'DisplayName', "ПОИ");
    hold on;
    grid on;
    assignin('base','poi3dPlot',poi3dPlot);
elseif (content == 3)
    Noize3dPlot = plot3(Info.x,Info.y,Info.z,'+','LineWidth',2,'DisplayName', "Шумы");
    hold on;
    grid on;
    assignin('base','Noize3dPlot',Noize3dPlot);
end

    
   

