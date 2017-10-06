#Code for tutorial found at 
#https://www.wzdftpd.net/blog/python-scripts-in-gdb.html


class PrintGList( gdb.Command ):
    """
    
    Glib Glist: wsd_print_glist list objecttpe

    Iterate through the list if nodes in a Glist and display
    a human-readable form of the objects.
    
    """

    def __init__( self ):
        
        gdb.Command.__init__( self, "wzd_print_glist", gdb.COMMAND_DATA, gdb.COMPLETE_SYMBOL, True)


    def invoke( self, arg, from_tty ):
        
        arg_list = gdb.string_to_argv( arg )

        if len( arg_list ) < 2:
            print( "Usage: wzd_print_glist list objectype" )
            return

        l = gdb.parse_and_eval( arg_list[0] )

        if l.type.code != gdb.lookup_type('GList').pointer().code:
            print( "%s is not a Glist*" % arg_list[0] )
            return

        try:
            t = gdb.lookup_type( arg_list[1] )
        except RuntimeError:
            print( "type %s not found" % arg_list[1] )
        
        # iterate list and print value
        while l:
            self._print_node(l, t)
            l = l['next']

    def _print_node( self, node, typeobject ):
        
        print( "Node at %s (prev: %s, next %s)" % (node, node['prev'], node['next'],) )
        data = node['data']
        pdata = data.cast( typeobject.pointer() )
        data = pdata.dereference()
        print( "Value: ", data )

PrintGList()
