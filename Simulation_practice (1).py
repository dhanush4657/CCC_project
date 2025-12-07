from manim import *
from . import nodeanimation

class LinkedListAnimation(Scene):
    def construct(self):
        # Introduction Text
        title = Text("Linked List", font_size=72).to_edge(UP)
        self.play(Write(title))
        self.wait(1)

        # Point 1: Nodes aligned and linked
        nodes = []
        for i in range(4):
            node = VGroup(
                Square(1), Square(1).next_to(RIGHT, buff=0),
                Text("data").move_to([-0.4, 0, 0]),
                Text("next").move_to([0.6, 0, 0])
            ).arrange(RIGHT, buff=0).shift(RIGHT * i * 2)
            nodes.append(node)
            self.add(node)

        self.wait(1)
        # Link Nodes
        links = []
        for j in range(len(nodes) - 1):
            link = Arrow(start=nodes[j][1].get_right(), end=nodes[j+1][0].get_left(), buff=0.1)
            links.append(link)
            self.play(Create(link))

        self.wait(2)

        # Point 2: Focus on one node
        self.play(FadeOut(*nodes[1:]), FadeOut(*links))
        focused_node = nodes[0].copy().scale(1.5).move_to(ORIGIN)
        self.play(Transform(nodes[0], focused_node))

        # Highlight data
        data_box = nodes[0][0]
        self.play(data_box.animate.set_fill(BLUE, opacity=0.5))
        self.wait(1)
        self.play(data_box.animate.set_fill(BLACK, opacity=0))

        # Highlight next
        next_box = nodes[0][1]
        self.play(next_box.animate.set_fill(BLUE, opacity=0.5))
        self.wait(1)
        self.play(next_box.animate.set_fill(BLACK, opacity=0))

        # Point 3: Scatter nodes and link
        scattered_nodes = []
        for i in range(4):
            node = VGroup(
                Square(1), Square(1).next_to(RIGHT, buff=0),
                Text("data").move_to([-0.4, 0, 0]),
                Text("next").move_to([0.6, 0, 0])
            ).arrange(RIGHT, buff=0).shift([i - 1.5, 2 - i, 0])
            scattered_nodes.append(node)
            self.add(node)

        scattered_links = []
        for j in range(len(scattered_nodes) - 1):
            link = Arrow(start=scattered_nodes[j][1].get_right(), end=scattered_nodes[j+1][0].get_left(), buff=0.1)
            scattered_links.append(link)
            self.play(Create(link))

        self.wait(2)

        # Point 4: Last node with NULL
        last_node = scattered_nodes[-1]
        self.play(last_node[1].animate.set_fill(BLUE, opacity=0.5))
        null_text = Text("NULL").move_to(last_node[1].get_center())
        self.play(Write(null_text))
        self.wait(2)

        # End Scene
        self.play(FadeOut(*self.mobjects))
