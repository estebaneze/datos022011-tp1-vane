/*
 * TestArbol.h
 *
 *  Created on: 21/10/2011
 *      Author: loo
 */

#ifndef TEST_H_
#define TEST_H_

class Test {
public:
        Test();
        virtual ~Test();
        void testABMDistrito();
        void testConteo();
        void agregarDistritos();
        void agregarVotantes();
        void firstSetTest();
        void ingresar();
        void pruebaListas();
        void pruebaListas2();
        void testEleccionesIndex();
        void testLogging();
        void Votar(Votante* votante);
        void testReportes();
        void testCandidato2();
        void testCandidato();
        void testConteo2();
        void testArbolVane();
        void Ingresar();
        void testConteo3();
        void testPersistorDistrito();
        void testPersistorConteo();
        void Votos();
};

#endif /* TEST_H_ */
