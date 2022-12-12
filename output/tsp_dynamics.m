clear;

num_cities = 8246;

log_data = readmatrix("ei8246_log.csv");
log_data(:, 1 : num_cities) = log_data(:, 1 : num_cities) + 1;

node_data = readmatrix("../ei8246_text.txt", 'Range', 8);
d_mat = zeros(num_cities, num_cities);

num_paths = size(log_data, 1);

t_schedule = log_data(:, num_cities + 1);
num_attempts = log_data(:, num_cities + 2);
num_changes = log_data(:, num_cities + 3);

for i = 1 : num_cities

    if mod(i, floor(num_cities/10)) == 0
        disp("Updating node i = " + i);
    end

    for j = i + 1 : num_cities

        xi = node_data(i, 2);
        yi = node_data(i, 3);

        xj = node_data(j, 2);
        yj = node_data(j, 3);

        dx = xi - xj;
        dy = yi - yj;
    
        d = sqrt(dx * dx + dy * dy);
        d_mat(i, j) = d;
        d_mat(j, i) = d;
    end
end

path_distances = zeros(1, num_paths);
for t = 1 : num_paths
    path = log_data(t, 1 : num_cities);

    distance = d_mat(path(1), path(num_cities));
    for i = 1 : num_cities - 1
        distance = distance + d_mat(path(i), path(i + 1));
    end
    path_distances(t) = distance;

end

figure;
path_distance_plot = plot(path_distances, '-b', 'LineWidth', 1.5);
hold on;
opt_path_plot = yline(206171, '--r', 'LineWidth', 1.5);
title("Path Length vs. Iteration t", 'Interpreter', 'latex', 'FontSize', 20);
subtitle("Optimal path length: $L_{*} = \;$" + 206171, 'Interpreter', 'latex', 'FontSize', 18);
xlabel("Iteration t", 'Interpreter', 'latex', 'FontSize', 16);
ylabel("Path Distance (km)", 'Interpreter', 'latex', 'FontSize', 16);
ylim([0 max(path_distances)]);
legend([path_distance_plot, opt_path_plot], ["$L_{t}$", "$L_{*}$"], 'Interpreter', 'latex', 'FontSize', 12);

figure;
scatter(node_data(:, 2), node_data(:, 3), 25, '.g');
camroll(90);


% fig = figure;
% gifFile = 'ei_plot.gif';
% for t = 1 : num_paths
% 
%     path = log_data(t, 1 : num_cities);
%     plot(node_data([path(1 : num_cities) path(num_cities) path(1)], 2), node_data([path(1 : num_cities) path(num_cities) path(1)], 3), '-b', 'LineWidth', 1.5);
%     title("Iteration t = " + t, 'Interpreter', 'latex', 'FontSize', 20);
%     subtitle("Path length: $L_{t} = \;$" + path_distance(t), 'Interpreter', 'latex', 'FontSize', 18);
%     %plot(node_data([path(num_cities) path(1)], 2), node_data([path(num_cities) path(1)], 3), '-b', 'LineWidth', 1.5);
%     %scatter(node_data(path(1), 2), node_data(path(1), 3), 'r', 'filled');
%     %set(gca, 'YDir', 'reverse');
%     camroll(90);
%     drawnow;
% %     frame = getframe(fig);
% %     im{t} = frame2im(frame);
% 
%     %exportgraphics(obj, gifFile, Append = true);
% 
% end

% for idx = 1 : num_paths
%     [A, map] = rgb2ind(im{idx}, 256);
%     if idx == 1
%         imwrite(A, map, gifFile, "gif","LoopCount", Inf);
%     elseif idx <= 100
%         imwrite(A, map, gifFile, "gif","WriteMode", "append");
%     elseif mod(idx, 10) == 0
%         imwrite(A, map, gifFile, "gif","WriteMode", "append");
%     end
% end
