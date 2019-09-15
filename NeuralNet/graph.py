import matplotlib.pyplot as plt
import numpy as np

class Graph(object):

    def __init__(self):
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111)
        self.lines = {}
        plt.ion()
        plt.show()
    
    def add_line(self, name, color="red"):
        self.lines[name], = self.ax.plot([], [], 'r-', color=color)
    
    def add_data(self, name, x, y):
        self.lines[name].set_xdata(np.append(self.lines[name].get_xdata(), x))
        self.lines[name].set_ydata(np.append(self.lines[name].get_ydata(), y))
    
    def add_axes_labels(self, label_x, label_y):
        plt.xlabel(label_x)
        plt.ylabel(label_y)
    
    def update(self):
        self.ax.relim()
        self.ax.autoscale_view()
        self.fig.canvas.draw()
        self.fig.canvas.flush_events()
    
    def ioff(self):
        plt.ioff()
        plt.show()
