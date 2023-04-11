

import nbh

name = "newtonian_black_hole.ppm"

nbh.run.run(nbh.setup.gravity,
            nbh.setup.stop,
            nbh.color.checker_board,
            nbh.euler.path,
            name)
