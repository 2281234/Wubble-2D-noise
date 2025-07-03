# Wubble-2D-noise
This program is a 2D black and white/RGB noise generator based on the Wubble cellular automaton.
Wubble cellular automaton rules:

There are 3 types of cells: empty (will be shown as a dot below), filled (will be shown as "#") and hatched ("="). Each cell looks at a 3 by 3 area, including itself, if there is a "#" in this area, then 1 is added to the cell counter, if the cell itself is "=", then one is also added. Also, for each pair of "=" in the corners (example: left up and right down) 1 is added to the cell counter. If the cell counter is 1, then it becomes "=", if 2, then "#", in other cases "." .

After generating the field states at each step of the cellular automaton, the field values ​​​​are set in the image, and then saved in Noise.png . The resulting image can be placed on textures or art to give them "liveliness" and "volume", or for other purposes.
