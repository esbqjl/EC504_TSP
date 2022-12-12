
files = dir("*_tours.csv*");

num_tests = length(files);
num_cities = zeros(1, num_tests);

mean_path = zeros(1, num_tests);
var_path = zeros(1, num_tests);

mean_runtime = zeros(1, num_tests);
var_runtime = zeros(1, num_tests);
average_percent_error = zeros(1, num_tests);

%                ar      bm      ca       dj    eg      ei      fi      gr
%optimal_paths = [837479; 959011; 1290319; 172386; 206171; 520527; 300899; 177092; 557315; 491924; 1061881; 427377; 86891; 96132; 114855; 9352; 26051; 855597; 394718; 79114; 569288; 27603; 238314; 95345];

optimal_paths = readmatrix("opt_tours.txt");


for k = 1 : num_tests
    
    current_file = files(k).name;
    country_id = current_file(1:2);
    num_cities(k) = str2num(current_file(3 : strfind(current_file, "_") - 1));
    disp("Country: " + country_id + ", num cities = " + num_cities(k) + ", opt path = " + optimal_paths(k));

    path_data = readmatrix(current_file);
    mean_path(k) = mean(path_data(:, end-1));
    var_path(k) = var(path_data(:, end-1));
    mean_runtime(k) = mean(path_data(:, end));
    var_runtime(k) = var(path_data(:, end));

    average_percent_error(k) = mean((path_data(:, end-1) - optimal_paths(k)) / optimal_paths(k));
    
    [sorted_cities, sorted_indices] = sort(num_cities);

end

figure;
scatter(num_cities, average_percent_error, 25, 'b', 'filled');
hold on;
yline(0.15, '--g', 'LineWidth', 1.5);
yline(0.10, '--g', 'LineWidth', 1.5);
yline(0.20, '--g', 'LineWidth', 1.5);
set(gca, 'xscale', 'log');
title("Simulated Annealing: Average Path Length Percent Error vs. Number of Cities", 'Interpreter', 'latex', 'FontSize', 20);
subtitle("$\bar{PE} = \frac{1}{T} \sum_{n=1}^{T} \frac{L_{n} - L_{*}}{L_{*}}, \; T = 30$ experiments", 'Interpreter', 'latex', 'FontSize', 18);
xlabel("(Log) Number of Cities", 'Interpreter', 'latex', 'FontSize', 16);
ylabel("Percent Error", 'Interpreter', 'latex', 'FontSize', 16);
ylim([0, 1.0]);

figure;
plot(sorted_cities, mean_runtime(sorted_indices), '-b', 'LineWidth', 1.5);
hold on;
errorbar(sorted_cities, mean_runtime(sorted_indices), sqrt(var_runtime(sorted_indices)), 'LineStyle', 'None', 'Color', 'r', 'LineWidth', 1.5);
title("Simulated Annealing: Run Time vs. Number of Cities", 'Interpreter', 'latex', 'FontSize', 20);
subtitle("Average Run-time for $T = 30$ experiments", 'Interpreter', 'latex', 'FontSize', 18);
set(gca, 'xscale', 'log');
set(gca, 'yscale', 'log');
xlabel("(Log) Number of Cities", 'Interpreter', 'latex', 'FontSize', 16);
ylabel("(Log) Run time (sec)", 'Interpreter', 'latex', 'FontSize', 16);

figure;
sim_plot = scatter(num_cities, mean_path, 25, 'b', 'filled');
hold on;
sim_plot2 = errorbar(num_cities, mean_path, sqrt(var_path), '.b');
op_path_plot = scatter(num_cities, optimal_paths, 25, 'r', 'filled');
title("Traveling Salesman Problem: Simulated Annealing", 'Interpreter', 'latex', 'FontSize', 20);
subtitle("Average path length for $T = 30$ experiments", 'Interpreter', 'latex', 'FontSize', 18);
set(gca, 'xscale', 'log');
set(gca, 'yscale', 'log');
xlabel("(Log) Number of Cities", 'Interpreter', 'latex', 'FontSize', 16);
ylabel("(Log) Path length (km)", 'Interpreter', 'latex', 'FontSize', 16);
legend([sim_plot, op_path_plot], ["Simulated Annealing Paths", "Optimal Paths"], 'Interpreter', 'latex', 'FontSize', 12, 'Location', 'southeast');

% for k = 1 : num_cities
%     xline(num_cities(k), '--k', 'LineWidth', 1.0);
% end

