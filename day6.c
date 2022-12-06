#include "stdio.h"
#include "stdlib.h"

// check for repetition in n-char buffer
int checkRepetition(char *, int);

// shift n-char buffer one place to left; lose the first byte
void shift(char *, int);

// find marker with size of markerSize
int getMarker(char *, int);


int main(int argc, char** argv) {
    char code[4096] = "wzsspbssbhshchmmrmprmrfrsfrrjhjphjjtppbfflqfqppdhdbhdhbbjgghgzgsgfsfhfhvvwcwhwwnppsbsggqnnvvtffpssjfjnnltntdtdddptprppjmmqssrlrplllfrrzggbmmlmnmtnnzddfdgfdfsstbstbbzcbbcjcvvfwwwzlzssglsgllnbnmbnmbbgmmppmwwsrrzqqvgqgnqnmmswwrnnbsnnbdbwwqnwqnwwzzqwzqzjqqwbqbccjcwwjlwjwppqfqjffwddrzrjzrjzzzhchjjlqqrggzvvnlvnvjvhvnvjvbbvdvldldbbwddtsscbbhccmbmbppbmmgjggcjjlrrwjwtjwwmffgddwvdvbdbvvhchmhmdmwwbjbjcbbcmbmmslmlslsjjrnrjrjpjcjgcjcjbbwsbsbfssjzsjsggcmcsswgssbbqpbqqdsdqqztzmzpmpbmbvbjjtrjtthwhbhnbhnbnssvpvsppgrrcwrrmqqhpphrpphchvhphqhbqbtttllsrlsrshrrmhmvvrmrnngbgnbnpbprrrftfjtjwwmrmvmcmvmrmwmssrccfbbhppjbpbwbqwbqbzzfmzmtttjbbvcvppmwwrbbzsbzbfzfdzzhrhzhvvsqvsqsnslljwllqlwllvccnttzhtzzpspqspqsqgsssvnsvshvsvqvnvlldbbfdfmmpbpgphhpqhpppchhbfbrfrllntnznrrhdrdhhdhjjgwwqhhfssjbjwjqqbffvvcrchccwmcwcllljtjrrqgrrdcrddvfvwvzzjqqcffgjgzzdhdwdssffjjhccggmtmltlhtthzhvhlvlddsfsbbtjbjcbjcjzcjjpfjfzzpnnbtbqtbqtqptpnplllbzbllhbllnqnttpddqvdqvqmmjnjggnnnhqqfcqcffqppdgpddvqddmhmrhrtrmrzmzhzpzlzqlqpqhphrpppjqqppzbzmmjgggqtggtjthhlclnclcnccmcppdcpddqrrfgrgbbhwhdhrrqtqpqjpqjpqjqqmcqmccnngqqqmtqtssnvnzvvpcpwcwwqcqqqfcqffsvsmvmttttmrrzssghgssjmsmbmvvwggggzhhfvdpgjmmvzbfjghqhrfbpmbvjzwvfmcthrqwdhghpwsspmhpqnmwhjzpnlzfnvhdnnrqwnvctbmjqzhqrpjlwrssdlwqzmsfrfzmgjhnwwnwczswnhsdbvqbmdlvntsdrhrjjcjjhpbblgwhjwdcdjtpvtmslwvncwdjbwzvbpzbvddvssnrhtshrcvnhqnpmjzfswqbbrztnwjcpflfbhnphfwmjvnvtswgfttgjcqcngmmwjlfsprwfcfwcmgrgbnqmzbtzbtbztngvrzpsnrzvhbsdjnzpwwzllgnfdrlwpmnrznqsqcmvnfbnhqjddvcjmtgbpbmsgqdqzflmlmqncmhwltrmdmgnwpfwddrdpfhsgsnggchzjhgpwrsmdzgjtrgmnprhbwbcbpzbdvvstfqcnqzbdjqpmrdbtgcthtclftghhmnrzrjqqsbndhpvmdpfpwdlhvmczvdfgvpqclssvlhqnhlcfnfbvtspdzmgzdctvpdcwchtqhpsgmmblspjdlvgblbpgrfrgnqqsphcsrgfsdmpqscbjmnqrfbcwfthdtswbzthpnvsfbntnbmmgpfzlqwhppvvdrmwbqzbgppbgsqmjfqtmntgwpnccthftwdmvwmnchlbjhsnmbhndczbrhhjpbvnjdzrcndbbmfwfwsjwfgbqhwhrsvlngsbhhlrdjzzbmjpsqhlpzwcsntjhlmngblspmsjrjwsjsrqwnrcwsmcsbmpjwrthbqhrschrmrppnnbmjbvjzlmzsrfdwqlfnfjljftjvzsqdwlhbblqcdlqjbprpcllhlhmwrbrlgfrcqshrtjpnmhljttdvpfnhdjqvjhhfczwvbzqgnzgljcfrbpgwnfhfchwzqmqqzpbcdpqmnbrppzblnnzqrfnmgtljwnfgzwvnjppdbdhbznvpgwhbdjjvlspgwgjsmfsvllpgwlfnnptmwnfsshjjvqzjwrqpvmsphpmftqdllqqdzcjwfvpftgvspprdwvvcnglmbpntghntdwpjvvsppgjvnbjgvtzchtqtwbddncsbrfcvrnvlggvwgmmnfzrswnzjrwthzmdsmzqmzsnrqsnslnhmfqljnnnzshqfqshrhhjmnhdgphctswdbhnrcgnzmmzqpjqbtdfhhltsmvvtntbgsznshhsghblhlhqpmdcfhmnfzvhgnfsfflcfwbfqzmccrjdpfvphtqbrdnzjfmfhbzqcpdnjdcgwprvchlzrcvrghgjqncjvnndbcshntrfsbsnmjlhclnzpfdgztflcpwqpnvlscfndwqzfvcmpgfncszpmwcsrdbrrhdjvmthslfvmlgpqhlgwhqnjljcvhswbsbqfrfhvzwjvdmhzsgbmbmfnbpclqdwhvrlpppszptjvwtvdmfltfqqgjttdggcvllblnnhjqnjzhvpgpzzpzwbpjqbthnjjlmsjgjzqwnjlqrcdmmvsldtcrzqdrcmwqhnhfghdlmzwcspgmlpzhbdsmlwlqnhhvcvdfzmvfwpbfmjtdllprfqzzjpbrshdzgspsrlrwrhdpmznzzqngwrzqpmtwgbsswrnnnfctjhbcftnslsqwjvmfwfdvfqcnsvfsvgstgbzpmljjtlvtnfsdzpvcgbjqwgbgzqbjfgltqvnhffflsbjzfqfrfbssrvvwqvqptmhrbgllqjwptrzgvqgccsrvbgtvmzfzlmtqrgfwhzddsptclbhjlwqfntvjqdvcddnffmbtqrnsvtmlvljcqdsrpggcmqvmmlzwwbgznhblwzjdppvtqzjvcmtfzhdzjplrdbrfrgzpldvnsgqlbwbmfvrbgwzmjmmqdfgwtbgtzmdqnvqbwvcfjhddqvnjtjlhhjnltbtqqvblwlmglrqcrcfjvdntrnqzzbmrjqglmrdcjgnshcghtprjqqsdrmgdnzmzcfqqdtjtrqgtqtgrpmmgzjtcrznmqccjbdpbvrnnbmbzvgdcnrczbctbrsrrqrjnfcdpzlnngwvcdtbbgssvhpptntqdzhcqtlpvzjbfgzggrgrcgtdfjbwdcrpztnfcdbscnlmqmwcbmtnddgbmhwsgvcfdcmhlsvtnqtmrnsjzhppgwvzlmhwwmpfjzrfbhsgntzrdhwswrnfmmmczqrvdrqnhgrvqbdddhglwsftsljvgbnjqfwfzsspdqvgsnlgfsfpvdrjhzcldtrmjjrmdhvvfrjldhhtqnvsvlldjpjbpwstfsmrpmbqbnnpvqtbgjvblthbmwqtfcfgnjscvtbvlqcmlhffpzgjzfscsqwnhrjhvbrrzwqvbjwtwhtqsdbssfgncppnsfgfltdcbjqjzqqtprsbvjzhmchnltvmbsvpvhgzhfhbrnttsqbcmwpdnwqqgdrjrdwdhtzwsmcdffqgsddvbzfjhtfhtnfdbfrwmdtcqshfjrcpswzcptgwgmctpmzjdbqlmqwthmnfplmctpsslcsdtqpqhjtmjdnmnqnjgchwstsmtpvsmgpsbfgwqnzhrdgdvcdlcldfcmjvsdldgbmhltjhczffwmzqssnhfnwftfgpshntjbpjdffjpcmcpwhclrrwqcqzmntjglzgcfrplfpvprtpvpjdlcrfwrtrzdzmhsrsmdcpqqrqgvfpdbmzbzqdfhpplmgfrdghclbclgswvwhhdvcpmpzflpffmptcrwglftztccrpbrvmpnqmqdgjgrrlbtqtvgcjpljttwtdslqjqlsdpblgrqbrtbmtblfbqtbvsqhpqzpqfhjqpmjrmcvqmsbbpjpdncgnjftclbltwszrrfzqbjcdtphcvpmbhppvwjwlprgmghrjzzgnvzlvghnjbzqjpdgzfsnjchpbzqdzpsjmsrvvqwjcpwznlpbjldlrdfqtrzhqzcnpjqbbbf";
    
    printf("%d\n", getMarker(code, 4));
    printf("%d\n", getMarker(code, 14));
    
    return 0;
}


int checkRepetition(char* buf, int n) {
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if (i==j) {
                continue;
            } else if (buf[i] == buf[j]) {
                return 1;
            }
        }
    }
    return 0;
}

void shift(char *buf, int n) {
    for (int i=0; i<n; ++i) {
        buf[i] = buf[i+1];
    }
}

int getMarker(char *code, int markerSize) {
    int marker;

    char *buffer = malloc(markerSize);
    for(int i=0; i<markerSize; i++) {
        buffer[i] = code[i];
    }

    for(int i=markerSize; i<4096; i++) {
        if(!checkRepetition(buffer, markerSize)) {
            marker = i;
            break;
        } else {
            shift(buffer, markerSize);
            buffer[markerSize-1] = code[i];
        }
    }

    free(buffer);

    return marker;
}