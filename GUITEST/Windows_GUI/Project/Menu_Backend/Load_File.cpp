#include "my_mainwindow.h"

/**************************************************************
 ************************FILE EXPLORER*************************
 *************************************************************/

/**
 * Each file Explorer shold follow this struct
 * 1. uint32_t Size of Data
 * 2. Data
 * /


/*
get_rx_rssi
set_rx_fir_config
get_rx_fir_config
rx_fastlock_load
set_tx_fir_config
get_tx_fir_config
tx_fastlock_load
set_trx_path_clks
trx_load_enable_fir
*/
class Parser
{
    public:
    std::vector<int> args;
    std::string input_string;
    std::string delimiter = ",";
    void comma_parser();
    void Write_to_mem();
};
Parser file_procesor;

void Parser::comma_parser()
{
    std::string token;
    size_t lim_pos;

    auto get_value = [&] ()-> int
    {
        lim_pos = input_string.find(delimiter); // find ","
        token   = input_string.substr(0,lim_pos);
        input_string.erase(0,lim_pos+1);
        return (int)(strtol(token.c_str(),NULL,10));
    };
    args.resize((size_t)get_value()); // allocate vector size
    std::generate (args.begin(), args.end(), get_value); // fill data parser
    std::for_each (args.begin(), args.end(), [](int i){std::cout << i << std::endl;});//print
}
void Parser::Write_to_mem()
{

}

void MainWindow ::Special_ones(int set_get)
{
    if(Set_param == set_get)
    {
        QString filter = "Text File (*.txt*) ;; All File (*.*)";
        QString file_name = QFileDialog::getOpenFileName(this,"List of Parameters",QDir::currentPath(),filter);
        QMessageBox::information(this,"struct selected",file_name);
        QFile file(file_name);
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"title", "file not open");
        }
        QTextStream in(&file);
        QString text = in.readAll();
        file.close();

        file_procesor.input_string = text.toUtf8().constData();
        file_procesor.comma_parser();
        Write_Special(file_procesor.args);
        file_procesor.args.clear();
    }

    
}

/*
int main(int argc, char const *argv[])
{

    comma_parser();
    return 0;
}
*/
