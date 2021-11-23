# include "object.hpp"

void check_color(vec3 & color)
{
	color = max(color, vec3(0.0, 0.0, 0.0));
	color = min(color, vec3(1.0, 1.0, 1.0));
}

void Object::update_transformation(mat4 m)
{
    vertices_transformed.clear();
    //boucle pour chaque vertives
    for(int i = 0; i < vertices.size(); i++)
    {
        vec4 v_res = m * vertices[i];
        vertices_transformed.push_back(v_res);
    }
	// TODO => TP02 //
}

void Object::update_projection(mat4 m)
{
	// TODO => TP02 //
}

void Object::draw(Window & window, vec4 light)
{
	for(unsigned int i=0; i<faces.size(); i++)
	{
		switch(draw_method)
		{
			case DRAW_WIRE :
				// TODO => TP02 //
				break;
			case DRAW_FILL :
				// TODO => TP03 //
				break;
			case DRAW_LAMBERT :
				// TODO => TP04 //
				break;
			case DRAW_GOURAUD :
				// TODO => TP04 //
				break;
			default :
				break;
		}
	}
}

void Object::backface_culling(mat4 trans_matrix)
{
	// TODO => TP03 //
}
