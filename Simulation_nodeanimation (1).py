from manim import *

class NodeAnimation(Scene):
    def construct(self):
        # Create the boxes
        box1 = Rectangle(width=2, height=1, color=WHITE)
        box2 = Rectangle(width=2, height=1, color=WHITE).next_to(box1, RIGHT, buff=0)
                
        # Create the labels
        data_label = Text("data", color=YELLOW).scale(1.0).next_to(box1, DOWN)
        next_label = Text("next", color=YELLOW).scale(1.0).next_to(box2, DOWN)
        node = VGroup(box1, box2, data_label, next_label)
        # Animation sequence
        self.play(Create(box1), Create(box2))
        self.play(Write(data_label), Write(next_label))
        self.wait(2)
