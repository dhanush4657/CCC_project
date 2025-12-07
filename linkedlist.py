from manim import *

class Node(VGroup):
    def __init__(self, width=2, data="data", next="next"):
        super().__init__()
        box1 = Rectangle(width=width, height=1, color=WHITE)
        box2 = Rectangle(width=width, height=1, color=WHITE).next_to(box1, RIGHT, buff=0)
        data_label = Text(data, color=YELLOW).scale(0.5).next_to(box1, DOWN)
        next_label = Text(next, color=YELLOW).scale(0.5).next_to(box2, DOWN)

        # Group all parts of the node together
        self.add(box1, box2, data_label, next_label)
        self.box1 = box1
        self.box2 = box2
        self.data_label = data_label
        self.next_label = next_label

class LinkedListScene(Scene):
    def construct(self):
        title = Text("Linked List", font_size=65).to_edge(UP)
        self.play(Write(title))
        self.wait(1)

        total_width = 6 +(2*3)
        if total_width > config.frame_width:
            scale_factor = config.frame_width / total_width * 0.9
        else:
            scale_factor = 0.9

        node1 = Node().scale(scale_factor).to_edge(LEFT)
        node2 = Node().scale(scale_factor).next_to(node1, RIGHT, buff=1)
        node3 = Node().scale(scale_factor).next_to(node2, RIGHT, buff=1)
        self.play(FadeIn(node1), FadeIn(node2), FadeIn(node3))
        self.wait(1)
        
        nodes = [node1, node2, node3]

        link_lines = []
        for i in range(len(nodes) - 1):
            start_point = nodes[i].next_label.get_bottom() + DOWN * 0.2
            mid_point_1 = start_point + DOWN * 1.0
            mid_point_2 = mid_point_1 + RIGHT * 2.80
            end_point = nodes[i+1].data_label.get_bottom() + DOWN * 0.2
            
            # Create the link line
            link_line = VMobject()
            link_line.set_points_as_corners([start_point, mid_point_1, mid_point_2, end_point])
            link_line.set_color(BLUE)
            link_lines.append(link_line)
        self.play(*[Create(line) for line in link_lines], run_time=0.8)
        self.wait(2)

        self.play(*[Uncreate(line)for line in link_lines])
        self.play(Uncreate(node2), Uncreate(node3))


        self.play(node1.animate.move_to([0,-1,0]).scale(2), runtime = 1.5)
        self.wait(7)

        self.play(node1.box1.animate.set_fill(BLUE, opacity=0.5))
        self.wait(1)
        data = Text("Actual data",color=WHITE, font_size=45).move_to(node1.box1.get_center())
        self.play(Write(data), run_time=1.5)
        self.wait(3)
        self.play(FadeOut(data), node1.box1.animate.set_fill(opacity=0))
        self.wait(1)

        self.play(node1.box2.animate.set_fill(BLUE, opacity=0.5))
        text = Text("Address of\nnext node", color=WHITE, font_size=40).move_to(node1.box2.get_center())
        self.play(Write(text), run_time=0.9)
        self.wait(5)
        self.play(FadeOut(text), node1.box2.animate.set_fill(opacity = 0))
        self.wait(1)

        name = always_redraw(
            lambda:Text("Dinesh", color = GREEN_D, font_size=30)
            .move_to(node1.box1.get_center()))
        self.play(Write(name))
        self.play(node1.animate.move_to(ORIGIN).to_edge(LEFT).scale(0.5), runtime = 0.8)
        
        node2 = Node().scale(scale_factor).next_to(node1, RIGHT, buff=2)
        self.play(Create(node2), runtime = 0.8)
        
        lastname = always_redraw(
            lambda:Text("504", color = GREEN_D, font_size=30).move_to(node2.box1.get_center()))
        self.play(Write(lastname))
        self.wait(8)

        arr1 = Node(width=1, data="1", next="2").scale(0.6).move_to([-2, -5, 0])
        arr2 = Node(width=1, data="3", next="4").scale(0.6).next_to(arr1, RIGHT, buff=0)
        arr3 = Node(width=1, data="5", next="6").scale(0.6).next_to(arr2, RIGHT, buff=0)
        arr4 = Node(width=1, data="7", next="8").scale(0.6).next_to(arr3, RIGHT, buff=0)
        array=VGroup(arr1, arr2, arr3, arr4)
        self.play(array.animate.shift(UP*2.5))
        self.wait(2)

        self.play(array.animate.shift(DOWN*3))
        self.play(FadeOut(array))
        self.wait(2)

        arrow= Arrow(
            start=node1.box2.get_center(),
            end=node2.box1.get_left(),
            color=BLUE,
            buff=0.2,
            stroke_width=4,
            max_tip_length_to_length_ratio=0.2
        )
        self.play(Create(arrow))
        self.wait(1.5)
        add1=Text("&node2", font_size=30, color=TEAL_D).move_to(node1.box2.get_center())
        self.play(
            Write(add1), 
            FadeOut(arrow)
        )
        self.wait(1)

        end=Text("Null",font_size=30, color=RED_D).move_to(node2.box2.get_center())
        self.play(Write(end))
        self.wait(1)

        hbox= Rectangle(width=2, height=1, color=WHITE).move_to([-4,-5,0])
        htext= always_redraw(
            lambda:Text("head", color=YELLOW).scale(0.5).next_to(hbox, DOWN)
        )
        head=VGroup(htext, hbox)

        self.play(head.animate.shift(UP*3))
        self.wait(4)

        self.play(FadeOut(node1),
                FadeOut(node2),
                FadeOut(add1),
                FadeOut(end),
                FadeOut(name),
                FadeOut(lastname),
                run_time=0.4
            )
        add=Text("\\0", color=RED_E, font_size=35).move_to(hbox.get_center())
        self.play(Write(add))
        self.wait(1)

        self.play(FadeIn(node1),
                  FadeIn(node2),
                  FadeIn(name),
                  FadeIn(lastname),
                  FadeIn(add1),
                  FadeIn(end)
                  
        )

        self.play(Unwrite(add))
        self.wait(1)

        line=Line(
            start=node1.data_label.get_bottom(),
            end=head.get_top(),
            color=RED_E
        )
        self.play(Create(line))

        add = Text("&node1", font_size=30, color=BLUE).move_to(hbox.get_center())
        self.play(Write(add))


        self.play(Uncreate(line))
        self.wait(10)

