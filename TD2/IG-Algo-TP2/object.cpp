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
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        vec4 v_res = m * vertices[i];
        vertices_transformed.push_back(v_res);
    }
	// TODO => TP02 //
	}

void Object::update_projection(mat4x3 m)
{
// TODO => TP02 //
	vec3 v_out;
	vertices_projected.clear();

	for(unsigned int i = 0; i < vertices_transformed.size(); i++)
	{
        v_out = m * vertices_transformed[i];
        vertices_projected.push_back(vec2(v_out / v_out.z));
	}
}

void Object::draw(Window & window, vec4 light)
{
	for(unsigned int i=0; i<faces.size(); i++)
	{
		switch(draw_method)
		{
			case DRAW_WIRE :
				for(unsigned int x = 0; x < 4; x++)
                {
                    vec2 p1 = vertices_projected[faces[i].vertex_index[x]];
                    vec2 p2 = vertices_projected[faces[i].vertex_index[(x + 1) % 4]];
                    window.draw_line(p1, p2, faces[i].color);
                }
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
