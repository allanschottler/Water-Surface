/* 
 * File:   OSGShaderFactory.h
 * Author: leomaia
 *
 * Created on December 2, 2014, 8:39 AM
 */

#ifndef OSGSHADERFACTORY_H
#define	OSGSHADERFACTORY_H

#include <osg/ref_ptr>
#include <osg/Program>

class OSGShaderFactory 
{
    public:
        
        /**
         * Retorna instancia do singleton
         * @return 
         */
        static OSGShaderFactory* getInstance();
        
        /**
         * Destroi instancia
         */
        static void destroy();
        
        /**
         * Destrutor
         */
        ~OSGShaderFactory();
        
        /**
         * Cria um programa baseado no caminho para o arquivo de shader
         * @param vertexProgramURL
         * @param fragmentProgramURL
         * @return 
         */
        osg::ref_ptr<osg::Program> createShaderProgram( const std::string& vertexProgram, const std::string& fragmentProgram );
        osg::ref_ptr<osg::Program> createShaderProgram( const std::string& vertexProgram, const std::string& geometryProgram, const std::string& fragmentProgram, int verticesOutEnum, int inputeTypeEnum, int outputTypeEnum );
        
    private:
        
        /**
         * Construtor privado
         */
        OSGShaderFactory();
        
        /**
         * Instancia unica
         */
        static OSGShaderFactory* _instance;
        
        // retorna um shader existente ou aloca caso nao exista
        osg::ref_ptr<osg::Shader> getShader( const std::string& shaderProgram, osg::Shader::Type type );
        
        typedef std::map< std::pair< std::string, osg::Shader::Type >, osg::ref_ptr<osg::Shader> > ShaderMap;
        
        // mapa de shaders alocado
        ShaderMap _shaderMap;

};

#endif	/* OSGSHADERFACTORY_H */

