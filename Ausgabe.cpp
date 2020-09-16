#include <iomanip>
#include "projekt13.h"


// Gebe Vektor vec[] mit Name name[] auf cout aus.
// Falls name[] == "", nur den Vektor.
void zeigeVektor ( char const name[], Bruch const vec[] )
{
    if ( name[ 0 ] != '\0' )
        cout << name << "[] = " ;
    cout << "[" ;
    for ( size_t i = 0 ;  i < Dim ;  ++i )
        cout << " " << vec[ i ] ;
    cout << " ]" << endl ;
}


// Gebe das lineare Gleichungssystem auf cout aus.
void zeigeLGS ( Bruch* const A[], Bruch const b[] )
{
    for ( size_t i = 0 ;  i < Dim ;  ++i )
    {
        for ( size_t j = 0 ;  j < Dim ;  ++j )
            cout << " " << setw( 6 ) << A[ i ][ j ] ;
        cout << " |" << setw( 4 ) << b[ i ] << endl ;
    }
    cout << endl ;

}  // zeigeLGS()


// Gebe das Polynom mit Koeffizienten koeff[] auf cout aus.
void zeigePolynom ( Bruch const koeff[] )
{
/***  behandle konstantes Polynom  ***/

    bool alleNull = true ;

    for ( size_t i = 1 ;  i < Dim ;  ++i )
        if ( koeff[ i ] != 0 )
        {
            alleNull = false ;
            break ;
        }

    // Polynom ist konstant
    if ( alleNull )
    {
        cout << koeff[ 0 ] << endl ;
        return ;
    }

/***  behandle nichtkonstantes Polynom  ***/

    bool erster = true ;

    for ( size_t i = 0 ;  i < Dim ;  ++i )
        if ( koeff[ i ] != 0 )
        {
            // gebe ersten Koeffizienten != 0 aus
            if ( erster )
            {
                if ( i == 0 )
                    cout << koeff[ i ] ;
                else if ( koeff[ i ] == -1 )
                    cout << "-" ;
                else if ( koeff[ i ] != 1 )
                    cout << koeff[ i ] << " " ;
            }

                // gebe sp鋞eren positiven Koeffizienten aus
            else if ( koeff[ i ] >= 0 )
            {
                cout << " + " ;
                if ( koeff[ i ] != 1 )
                    cout << koeff[ i ] << " " ;
            }

                // gebe sp鋞eren negativen Koeffizienten aus
            else
            {
                cout << " - " ;
                if ( koeff[ i ] != -1 )
                    cout << -koeff[ i ] << " " ;
            }

            // gebe Potenz aus
            if ( i >= 1 )
            {
                cout << "x" ;
                if ( i >= 2 )
                    cout << "^" << i ;
            }

            // erster Koeffizient != 0 jetzt ausgegeben
            erster = false ;
        }

    cout << endl ;

}  // zeigePolynom()
