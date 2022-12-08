import matplotlib.pyplot as plt
import sys


def plotTSP(paths, points, num_iters=1):
    """
    path: List of lists with the different orders in which the nodes are visited
    points: coordinates for the different nodes
    num_iters: number of paths that are in the path list

    """

    # Unpack the primary TSP path and transform it into a list of ordered
    # coordinates

    x = [];
    y = []
    for i in paths[0]:
        x.append(points[i][0])
        y.append(points[i][1])

    plt.scatter(x,y,1)

    # Set a scale for the arrow heads (there should be a reasonable default for this)
    a_scale = float(max(x)) / float(100000)

    # Draw the older paths, if provided
    if num_iters > 1:

        for i in range(1, num_iters):

            # Transform the old paths into a list of coordinates
            xi = [];
            yi = [];
            for j in paths[i]:
                xi.append(points[j][0])
                yi.append(points[j][1])

            plt.arrow(xi[-1], yi[-1], (xi[0] - xi[-1]), (yi[0] - yi[-1]), head_width=a_scale, color='r',
                      length_includes_head=True, ls='dashed',
                      width=0.001 / float(num_iters))
            for i in range(0, len(x) - 1):
                plt.arrow(xi[i], yi[i], (xi[i + 1] - xi[i]), (yi[i + 1] - yi[i]),
                          head_width=a_scale, color='r', length_includes_head=True,
                          ls='dashed', width=0.001 / float(num_iters))

    # Draw the primary path for the TSP problem
    plt.arrow(x[-1], y[-1], (x[0] - x[-1]), (y[0] - y[-1]), head_width=a_scale,
              color='g', length_includes_head=True)
    for i in range(0, len(x) - 1):
        plt.arrow(x[i], y[i], (x[i + 1] - x[i]), (y[i + 1] - y[i]), head_width=a_scale,
                  color='g', length_includes_head=True)

    # Set axis too slitghtly larger than the set of x and y
    plt.xlim(min(x) -100, max(x) +100)
    plt.ylim(min(y) -100, max(y) +100)
    plt.show()


if __name__ == '__main__':
    with open(sys.argv[1], 'r') as token:

        # token = open('data_800.tsp','r')
        linestoken = token.readlines()
        tokens_column_number = 1
        resulttoken_x = []
        resulttoken_y = []
        resulttoken_id = []
        for x in linestoken:
            if linestoken.index(x)<7:
                continue
            else:
                resulttoken_x.append(float(x.split()[tokens_column_number]))
            # print(x)

        tokens_column_number += 1;
        for x in linestoken:
            if linestoken.index(x)<7:
                continue
            else:
                resulttoken_y.append(float(x.split()[tokens_column_number]))
        for x in linestoken:
            if linestoken.index(x)<7:
                continue
            else:
                resulttoken_id.append(x.split()[0])
    with open(sys.argv[2], 'r') as token:
        # token = open('result3.tsp', 'r')
        linestoken = token.readlines()
        tokens_column_number2 = 0

        resulttoken = []
        for x in linestoken:
            resulttoken.append(x.split()[tokens_column_number2])

        token.close()
        xiabiao = []
        for x in resulttoken:
            xiabiao.append(resulttoken_id.index(x))
        # print(resulttoken_x)
        # print(resulttoken_y)
        # print(resulttoken_id)
        # print(resulttoken)
        # print(xiabiao)

        # Create a randomn list of coordinates, pack them into a list
        # x_cor = [1, 8, 4, 9, 2, 1, 8]
        # y_cor = [1, 2, 3, 4, 9, 5, 7]
        points = []
        for i in range(0, len(resulttoken_x)):
            points.append((resulttoken_x[i], resulttoken_y[i]))

        # Create two paths, teh second with two values swapped to simulate a 2-OPT
        # Local Search operation
        # path4 = [0, 1, 2, 3, 4, 5, 6]
        # path3 = [0, 2, 1, 3, 4, 5, 6]
        # path2 = [0, 2, 1, 3, 6, 5, 4]
        # path1 = [0, 2, 1, 3, 6, 4, 5]

        # Pack the paths into a list
        # paths = [path1, path2, path3, path4]
        paths = [xiabiao]

        # Run the function
        plotTSP(paths, points, 1)
